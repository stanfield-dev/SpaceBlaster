#pragma once

#include "EntityManager.h"
#include "Entity.h"

class Projectile : public Entity
{
private:
	void rotateProjectile();

public:
	Projectile(int, float, float, float, int, EntityManager*);
	Projectile(int, float, float, float, int, float*, float*, EntityManager*);
	~Projectile();
	
	void moveProjectile() override;
};