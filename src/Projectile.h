#pragma once

#include "Entity.h"

class Projectile : public Entity
{
private:

public:
	Projectile(int, float, float, float, int);
	~Projectile();
};