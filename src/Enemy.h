#pragma once

#include "EntityManager.h"
#include "Entity.h"

class Enemy : public Entity
{
private:

public:
	Enemy(int, float, float, float, EntityManager*);
	~Enemy();
};

