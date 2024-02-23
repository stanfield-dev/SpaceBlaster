#pragma once

#include "EntityManager.h"
#include "Entity.h"

class HealthBar : public Entity
{
private:
	int m_livesRemaining = 3;

public:
	HealthBar(int, float, float, float, EntityManager*);
	~HealthBar();

	void updateLives(int) override;
};