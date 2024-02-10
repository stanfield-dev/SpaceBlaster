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
		case PROJECTILE	:	newEntity = new Projectile(type, x, y, z, projectileSource); // TODO have projectile x-axis movement based on projectileSource
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
	for (auto anentity : m_entityRegistry) {
		std::cout << anentity->getType() << std::endl;
	}
	std::cin.get();

	return m_entityRegistry;
}
