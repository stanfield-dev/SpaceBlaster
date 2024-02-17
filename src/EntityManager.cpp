#include "EntityManager.h"
#include "Entity.h"
#include "Enemy.h"
#include "Explosion.h"
#include "Player.h"
#include "Projectile.h"

#include <iostream>
#include <iterator>

EntityManager::EntityManager(ma_engine* soundEngine)
{
	m_soundEngine = soundEngine;
}

EntityManager::~EntityManager()
{
}

Entity* EntityManager::spawnEntity(int type, float x, float y, float z, int projectileSource,
	float* sourceCoordinates, float* targetCoordinates)
{
	Entity* newEntity = nullptr;

	switch (type) {
		case ENEMY		:	newEntity = new Enemy(type, x, y, z, this);
							break;
		case EXPLOSION	:	newEntity = new Explosion(type, x, y, z, this);
							break;
		case PLAYER		:	newEntity = new Player(type, x, y, z, this);
							break;
		case PROJECTILE:	if (projectileSource == PLAYER) {
								newEntity = new Projectile(type, x, y, z, projectileSource, this);
							}
							else {
								newEntity = new Projectile(type, x, y, z, projectileSource,
															sourceCoordinates, targetCoordinates, this);
							}
							ma_engine_play_sound(m_soundEngine, PROJECTILE_SOUND.c_str(), NULL);
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
									if (target->getType() == ENEMY) {
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
											return;
										}
									}
								}
				case ENEMY	:	for (auto target : m_entityRegistry) {
									if (target->getType() == PLAYER) {
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
											return;
										}
									}
								}
				default		:	if (entity->getPositionX() < -1.0f || entity->getPositionX() > 1.0f) {
									removeEntityFromRegistry(entity);
									entity->~Entity();
									delete entity;
								}
			}
		}
	}
}


