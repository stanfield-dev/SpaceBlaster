#pragma once

#include "EntityManager.h"
#include "Entity.h"

class Projectile : public Entity
{
private:
	float m_projectileVelocity = 0.025f;
	void rotateProjectile();

public:
	Projectile(int, float, float, float, int, EntityManager*);
	Projectile(int, float, float, float, int, float*, float*, EntityManager*);
	~Projectile();
	
	void moveProjectile() override;
};