#pragma once	

#include <vector>

#include "defines.h"
#include "Entity.h"


static class Manager
{
private:
	std::vector<Entity*> entityRegistry;

public:
	static void addEntity(Entity*);
	static void removeEntity(Entity*);

	static std::vector<Entity*> EntityRegistry();
};
