#pragma once

#include "EntityManager.h"
#include "Entity.h"

class GameOver : public Entity
{
private:
	int m_frame = 0;

public:
	GameOver(int, float, float, float, EntityManager*);
	~GameOver();

	void animateScreen() override;
};
