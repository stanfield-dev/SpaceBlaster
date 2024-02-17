#pragma once

#include "EntityManager.h"
#include "Entity.h"

class Player : public Entity
{
private:

public:
	Player(int, float, float, float, EntityManager*);
	~Player();
};

