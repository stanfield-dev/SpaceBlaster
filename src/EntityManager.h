#pragma once	

#include <vector>

#include "defines.h"
#include "Entity.h"


static class EntityManager
{
private:
	static inline std::vector<Entity*> m_entityRegistry;

public:
	static Entity* spawnEntity(int, float, float, float, int);

	static void addEntityToRegistry(Entity*);
	static void removeEntityFromRegistry(Entity*);

	static std::vector<Entity*> getEntityRegistry();
};
