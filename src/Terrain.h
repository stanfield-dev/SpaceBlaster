#pragma once

#include "EntityManager.h"
#include "Entity.h"

class Terrain : public Entity
{
private:

public:
	Terrain(int, float, float, float, EntityManager*);
	~Terrain();
};
