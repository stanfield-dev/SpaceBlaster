#pragma once

#include "EntityManager.h"
#include "Entity.h"

class HealthBar : public Entity
{
private:

public:
	HealthBar(int, float, float, float, EntityManager*);
	~HealthBar();

	int m_livesRemaining = 3;
	
	void updateHealthBarLives(int) override;
};