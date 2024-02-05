#pragma once

#include "defines.h"

class Enemy
{
private:
	const float m_enemySpriteSheetWidth = 4096.0f;
	const float m_enemySpriteSheetHeight = 512.0f;
	const float m_enemySpriteWidth = 512.0f;
	const float m_enemySpriteHeight = 512.0f;

	// arbitary starting position defaults
	float m_enemyPosX = 0.5f;
	float m_enemyPosY = 0.3f;

	float m_xOffset = ENEMYWIDTH / SCREENWIDTH;
	float m_yOffset = ENEMYHEIGHT / SCREENHEIGHT;

	float m_spriteXOrigin = 0.0f;
	float m_spriteXOffset = m_enemySpriteWidth / m_enemySpriteSheetWidth;
	float m_spriteYOrigin = 0.0f;
	float m_spriteYOffset = m_enemySpriteHeight / m_enemySpriteSheetHeight;

	float m_enemyVertices[20] = {
		m_enemyPosX, m_enemyPosY,
		m_spriteXOrigin, m_spriteYOrigin,
		(float)ENEMY,

		m_enemyPosX + m_xOffset, m_enemyPosY,
		m_spriteXOrigin + m_spriteXOffset, m_spriteYOrigin,
		(float)ENEMY,

		m_enemyPosX + m_xOffset, m_enemyPosY + m_yOffset,
		m_spriteXOrigin + m_spriteXOffset, m_spriteYOrigin + m_spriteYOffset,
		(float)ENEMY,

		m_enemyPosX, m_enemyPosY + m_yOffset,
		m_spriteXOrigin, m_spriteYOrigin + m_spriteYOffset,
		(float)ENEMY
	};

public:

	Enemy();
	~Enemy();

	float getPosX() const;
	float getPosY() const;
	void setPosX(float);
	void setPosY(float);

	void init();
	void updatePosX(float);
	void updatePosY(float);
	float* calculateEnemyPosition();
	void updateEnemyVertices(float*);
	void fireEngines();
};

