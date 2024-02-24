#pragma once

#include "EntityManager.h"
#include "Entity.h"

class GameOver : public Entity
{
private:
	int m_timer = 0;

public:
	GameOver(int, float, float, float, EntityManager*);
	~GameOver();

	void incrementTimer();
	int getTimer() const;
};
