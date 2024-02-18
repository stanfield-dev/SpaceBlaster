#pragma once

#pragma once

#include "EntityManager.h"
#include "Entity.h"

class Explosion : public Entity
{
private:

public:
	Explosion(int, float, float, float, EntityManager*);
	~Explosion();

	void animateExplosion() override;
	int getExplosionFrame() const override;
};