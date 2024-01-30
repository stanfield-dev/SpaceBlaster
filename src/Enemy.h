#pragma once

#include "defines.h"

class Enemy
{
private:
	const float m_enemySpriteSheetWidth = 4096.0f;
	const float m_enemySpriteSheetHeight = 512.0f;
	const float m_enemySpriteWidth = 512.0f;
	const float m_enemySpriteHeight = 512.0f;

	float m_xOffset = PLAYERWIDTH / SCREENWIDTH;
	float m_yOffset = PLAYERHEIGHT / SCREENHEIGHT;
	float m_enemyPosX = 0.15f;
	float m_enemyPosY = 0.23f;

	float m_spriteXOrigin = 0.0f;
	float m_spriteXOffset = m_enemySpriteWidth / m_enemySpriteSheetWidth;
	float m_spriteYOrigin = 0.0f;
	float m_spriteYOffset = m_enemySpriteHeight / m_enemySpriteSheetHeight;

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

