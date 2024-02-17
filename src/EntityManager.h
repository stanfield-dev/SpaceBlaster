#pragma once	

#include <vector>

#include "defines.h"
#include "Entity.h"

#include "miniaudio.h"

static class EntityManager
{
private:
	static inline std::vector<Entity*> m_entityRegistry;

public:
	static Entity* spawnEntity(int, float, float, float, int, float*, float*);

	static void addEntityToRegistry(Entity*);
	static void removeEntityFromRegistry(Entity*);

	static std::vector<Entity*> getEntityRegistry();

	static void updateVertexBuffers();

	static void checkCollisions(ma_engine*);
};
