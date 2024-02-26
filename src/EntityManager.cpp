#include "EntityManager.h"
#include "Background.h"
#include "Countdown.h"
#include "Entity.h"
#include "Enemy.h"
#include "Explosion.h"
#include "GameOver.h"
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
		case PROJECTILE: 
			{
				if (source == PLAYER) {
					newEntity = new Projectile(type, x, y, z, source, this);
				}
				else {
					newEntity = new Projectile(type, x, y, z, source,
						sourceCoordinates, targetCoordinates, this);
				}
				ma_engine_play_sound(m_soundEngine, PROJECTILE_SOUND.c_str(), NULL);
			}
			break;
		case EXPLOSION:
			{
				newEntity = new Explosion(type, x, y, z, this);
			}
			break;
		case ENEMY:	
			{
				newEntity = new Enemy(type, x, y, z, this);
			}
			break;
		case PLAYER:	
			{
				newEntity = new Player(type, x, y, z, this);
			}
			break;
		case COUNTDOWN:	
			{
				newEntity = new Countdown(type, x, y, z, source, this);
			}
			break;
		case SCORE:	
			{
				newEntity = new Score(type, x, y, z, this);
			}
			break;
		case STARTSCREEN:	
			{
				newEntity = new StartScreen(type, x, y, z, this);
			}
			break;
		case HELPSCREEN:	
			{
				newEntity = new HelpScreen(type, x, y, z, this);
			}
			break;
		case BACKGROUND:	
			{
				newEntity = new Background(type, x, y, z, this);
			}
			break;
		case HEALTHBAR:	
			{
				newEntity = new HealthBar(type, x, y, z, this);
			}
			break;
		case GAMEOVER:	
			{
				newEntity = new GameOver(type, x, y, z, this);
			}
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
	if (loc != m_entityRegistry.end()) {
		m_entityRegistry.erase(loc);
	}
}

std::vector<Entity*> EntityManager::getEntityRegistry()
{
	return m_entityRegistry;
}

Entity* EntityManager::getEntity(int entityType)
{
	if ((entityType == PROJECTILE) || entityType == EXPLOSION) {
		// could be more than one, and these should never arrive as entityTypes
		return nullptr;
	}

	for (auto entity : m_entityRegistry) {
		if (entity->getType() == entityType) {
			return entity;
		}
	}

	return nullptr;
}

void EntityManager::resetPlayerLivesRemaining()
{
	m_playerLivesRemaining = 3;
}

void EntityManager::updatePlayerLivesRemaining(int x)
{
	m_playerLivesRemaining += x;

	Entity* healthBar = getEntity(HEALTHBAR);
	healthBar->updateHealthBarLives(x);
}

int EntityManager::getPlayerLivesRemaining() const
{
	return m_playerLivesRemaining;
}

void EntityManager::updateVertexBuffers()
{
	for (auto entity : m_entityRegistry) {
		entity->updateVertexBuffer();
	}
}

void EntityManager::resetEnemyDifficulty()
{
	m_enemyDifficulty = 0.0f;
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
		m_enemyDifficulty += 0.0015f;
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


