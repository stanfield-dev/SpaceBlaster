#pragma once

#include "EntityManager.h"
#include "Entity.h"

class Countdown : public Entity
{
private:

public:
	Countdown(int, float, float, float, int, EntityManager*);
	~Countdown();

	void animateCountdown() override;
	int getCountdownFrame() const override;
};