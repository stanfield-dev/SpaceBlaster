#include "EntityManager.h"
#include "Background.h"
#include "Countdown.h"
#include "Entity.h"
#include "Enemy.h"
#include "Explosion.h"
#include "StartScreen.h"
#include "HealthBar.h"
#include "HelpScreen.h"
#include "Player.h"
#include "Projectile.h"
#include "Score.h"

#include <iostream>
#include <iterator>

EntityManager::EntityManager(ma_engine* soundEngine)
{
	m_soundEngine = soundEngine;
}

EntityManager::~EntityManager()
{
}

Entity* EntityManager::spawnEntity(int type, float x, float y, float z, int source,
	float* sourceCoordinates, float* targetCoordinates)
{
	Entity* newEntity = nullptr;

	switch (type) {
		case PROJECTILE	:	if (source == PLAYER) {
								newEntity = new Projectile(type, x, y, z, source, this);
							}
							else {
								newEntity = new Projectile(type, x, y, z, source,
														sourceCoordinates, targetCoordinates, this);
							}
							ma_engine_play_sound(m_soundEngine, PROJECTILE_SOUND.c_str(), NULL);
							break;
		case EXPLOSION	:	newEntity = new Explosion(type, x, y, z, this);
							break;
		case ENEMY		:	newEntity = new Enemy(type, x, y, z, this);
							break;
		case PLAYER		:	newEntity = new Player(type, x, y, z, this);
							break;
		case COUNTDOWN	:	newEntity = new Countdown(type, x, y, z, source, this);
							break;
		case SCORE		:	newEntity = new Score(type, x, y, z, this);
							break;
		case STARTSCREEN	:	newEntity = new StartScreen(type, x, y, z, this);
							break;
		case HELPSCREEN	:	newEntity = new HelpScreen(type, x, y, z, this);
							break;
		case BACKGROUND	:	newEntity = new Background(type, x, y, z, this);
							break;
		case HEALTHBAR	:	newEntity = new HealthBar(type, x, y, z, this);
							break;
	}
	
	return newEntity;
}

void EntityManager::addEntityToRegistry(Entity* entity)
{
	m_entityRegistry.push_back(entity);
}

void EntityManager::removeEntityFromRegistry(Entity* entity)
{
	auto loc = std::find(m_entityRegistry.begin(), m_entityRegistry.end(), entity);
	if(loc != m_entityRegistry.end()) {
		m_entityRegistry.erase(loc);
	}
}

std::vector<Entity*> EntityManager::getEntityRegistry()
{
	return m_entityRegistry;
}

Entity* EntityManager::getCountdownEntity()
{
	if (countdownEntity == nullptr) {
		for (auto entity : m_entityRegistry) {
			if (entity->getType() == COUNTDOWN) {
				return entity;
			}
		}
	}
	return 0;
}

Entity* EntityManager::getPlayerEntity()
{
	if (playerEntity == nullptr) {
		for (auto entity : m_entityRegistry) {
			if (entity->getType() == PLAYER) {
				return entity;
			}
		}
	}
	return 0;
}

void EntityManager::setLivesRemaining(int x)
{
	m_playerLivesRemaining += x;

	if (m_playerLivesRemaining == 0) {
		// TODO game over, but for now...
		m_playerLivesRemaining = 3;
		for (auto entity : m_entityRegistry) {
			if (entity->getType() == HEALTHBAR) {
				entity->updateLives(-2);
			}
		}
	}
	else {
		for (auto entity : m_entityRegistry) {
			if (entity->getType() == HEALTHBAR) {
				entity->updateLives(x);
			}
		}
	}
}

int EntityManager::getLivesRemaining() const
{
	return m_playerLivesRemaining;
}

void EntityManager::updateScore()
{
	for (auto entity : m_entityRegistry) {
		if (entity->getType() == SCORE) {
			entity->updateScore();
		}
	}
}

void EntityManager::updateVertexBuffers()
{
	for (auto entity : m_entityRegistry) {
		entity->updateVertexBuffer();
	}
}

void EntityManager::checkCollisions()
{
	for (auto entity : m_entityRegistry) {
		if (entity->getType() == PROJECTILE) {
			switch (entity->getProjectileSource()) {
				case PLAYER	:	for (auto target : m_entityRegistry) {
									if (target->getType() == ENEMY) { // enemy is destroyed
										if ((entity->getRightEdge() > target->getLeftEdge()) &&
											(entity->getRightEdge() < target->getRightEdge()) &&
											(entity->getTopEdge() > target->getBottomEdge()) &&
											(entity->getTopEdge() < target->getTopEdge()))
										{
											spawnEntity(EXPLOSION,
														target->getPositionX(),
														target->getPositionY(),
														target->getPositionZ(),
														EXPLOSION, nullptr, nullptr);
											ma_engine_play_sound(m_soundEngine, EXPLOSION_SOUND.c_str(), NULL);
											removeEntityFromRegistry(entity);
											entity->~Entity();
											delete entity;
											removeEntityFromRegistry(target);
											target->~Entity();
											delete target;
											updateScore();
											spawnEntity(COUNTDOWN,
												0.0f - ((COUNTDOWNWIDTH/SCREENWIDTH) / 2),
												0.0f,
												0.0f,
												ENEMY, nullptr, nullptr);
											return;
										}
									}
								}
								[[fallthrough]]; // never end up here, but tired of seeing the compiler warning

				case ENEMY	:	for (auto target : m_entityRegistry) {
									if (target->getType() == PLAYER) { // player is destroyed
										if ((entity->getLeftEdge() < target->getRightEdge()) &&
											(entity->getLeftEdge() > target->getLeftEdge()) &&
											(entity->getTopEdge() > target->getBottomEdge()) &&
											(entity->getTopEdge() < target->getTopEdge()))
										{
											spawnEntity(EXPLOSION,
														target->getPositionX(),
														target->getPositionY(),
														target->getPositionZ(),
														EXPLOSION, nullptr, nullptr);
											ma_engine_play_sound(m_soundEngine, EXPLOSION_SOUND.c_str(), NULL);
											removeEntityFromRegistry(entity);
											entity->~Entity();
											delete entity;
											removeEntityFromRegistry(target);
											target->~Entity();
											delete target;
											setLivesRemaining(-1);
											spawnEntity(COUNTDOWN,
												0.0f - ((COUNTDOWNWIDTH / SCREENWIDTH) / 2),
												0.0f,
												0.0f,
												PLAYER, nullptr, nullptr);
											return;
										}
									}
								}
								[[fallthrough]]; // never end up here, but tired of seeing the compiler warning

				default		:	if (entity->getPositionX() < -1.0f || entity->getPositionX() > 1.0f) {
									removeEntityFromRegistry(entity);
									entity->~Entity();
									delete entity;  // projectile moved offscreen and is destroyed
								}
			}
		}
	}
}

Entity* EntityManager::respawnEnemy()
{
	int e = 0;

	for (auto entity : m_entityRegistry) {
		if (entity->getType() == ENEMY) {
			e = 1;
		}
	}
	
	if (!e) {
		m_enemyDifficulty += 0.001f;
		Entity* enemy = spawnEntity(ENEMY, 0.7f, 0.0f, 0.0f, ENEMY, nullptr, nullptr);
		enemy->increaseDifficulty(m_enemyDifficulty);
		return enemy;
	}
}

Entity* EntityManager::respawnPlayer()
{
	int p = 0;

	for (auto entity : m_entityRegistry) {
		if (entity->getType() == PLAYER) {
			p = 1;
		}
	}

	if (!p) {
		Entity* player = spawnEntity(PLAYER, -0.9f, 0.0f, 0.0f, PLAYER, nullptr, nullptr);
		return player;
	}
}


