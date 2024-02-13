#include "EntityManager.h"
#include "Entity.h"
#include "Enemy.h"
#include "Player.h"
#include "Projectile.h"

#include <iostream>
#include <iterator>

Entity* EntityManager::spawnEntity(int type, float x, float y, float z, int projectileSource)
{
	Entity* newEntity = nullptr;

	switch (type) {
		case PLAYER		:	newEntity = new Player(type, x, y, z);
							break;
		case ENEMY		:	newEntity = new Enemy(type, x, y, z);
							break;
		case PROJECTILE	:	newEntity = new Projectile(type, x, y, z, projectileSource); 
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
			// CASE: projectile hits edge of screen
			if (entity->getPositionX() < -1.0f || entity->getPositionX() > 1.0f) {
				removeEntityFromRegistry(entity);
				entity->~Entity();
				delete entity;
			}

			// CASE: player projectile hits enemy
			if (entity->getProjectileSource() == PLAYER) {
				for (auto target : m_entityRegistry) {
					if (target->getType() == ENEMY) {
						if ( (entity->getRightEdge() > target->getLeftEdge()) &&
							(entity->getRightEdge() < target->getRightEdge()) &&
							(entity->getTopEdge() > target->getBottomEdge()) &&
							(entity->getTopEdge() < target->getTopEdge()) )
						{
							target->projectileImpact();
							removeEntityFromRegistry(entity);
							entity->~Entity();
							delete entity;
							return;
						}
					}
				}
			}

			// CASE: enemy projectile hits player
			if (entity->getProjectileSource() == ENEMY) {
				for (auto target : m_entityRegistry) {
					if (target->getType() == PLAYER) {
						if ((entity->getLeftEdge() > target->getRightEdge()) &&
							(entity->getLeftEdge() < target->getLeftEdge()) &&
							(entity->getTopEdge() > target->getBottomEdge()) &&
							(entity->getTopEdge() < target->getTopEdge()))
						{
							target->projectileImpact();
							removeEntityFromRegistry(entity);
							entity->~Entity();
							delete entity;
							return;
						}
					}
				}
			}
		}
	}
}


