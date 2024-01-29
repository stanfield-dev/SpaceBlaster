#pragma once

#include "defines.h"

class Enemy
{
private:
	float m_xOffset = PLAYERWIDTH / SCREENWIDTH;
	float m_yOffset = PLAYERHEIGHT / SCREENHEIGHT;
	float m_enemyPosX = 0.15f;
	float m_enemyPosY = 0.23f;
	float m_enemyVertices[20];

public:

	Enemy();
	~Enemy();

	float getPosX();
	float getPosY();
	void setPosX(float);
	void setPosY(float);

	void init();
	void updatePosX(float);
	void updatePosY(float);
	float* calculateEnemyPosition();
	void updateEnemyVertices(float*);
};

