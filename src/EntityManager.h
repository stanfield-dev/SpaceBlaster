#pragma once	

#include <vector>

#include "defines.h"
#include "Entity.h"

#include "miniaudio.h"

class EntityManager
{
private:
	ma_engine* m_soundEngine;
	std::vector<Entity*> m_entityRegistry;

public:
	EntityManager(ma_engine*);
	~EntityManager();

	Entity* spawnEntity(int, float, float, float, int, float*, float*);

	void addEntityToRegistry(Entity*);
	void removeEntityFromRegistry(Entity*);

	std::vector<Entity*> getEntityRegistry();

	void updateVertexBuffers();

	void checkCollisions();
};
