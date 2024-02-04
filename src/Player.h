#pragma once

#include <array>
#include "defines.h"

class Player 
{
private:
	const float m_playerSpriteSheetWidth = 4096.0f;
	const float m_playerSpriteSheetHeight = 512.0f;
	const float m_playerSpriteWidth = 512.0f;
	const float m_playerSpriteHeight = 512.0f;

	float m_xOffset = PLAYERWIDTH / SCREENWIDTH;
	float m_yOffset = PLAYERHEIGHT / SCREENHEIGHT;

	// arbitary starting position defaults
	float m_playerPosX = -0.9f;
	float m_playerPosY = 0.0f;

	float m_spriteXOrigin = 0.0f;
	float m_spriteXOffset = m_playerSpriteWidth / m_playerSpriteSheetWidth;
	float m_spriteYOrigin = 0.0f;
	float m_spriteYOffset = m_playerSpriteHeight / m_playerSpriteSheetHeight;

	float m_playerVertices[20];

public:

	Player();
	~Player();

	float getPosX() const;
	float getPosY() const;
	float getGunPosition() const;

	void setPosX(float);
	void setPosY(float);

	void init();
	void updatePosX(float);
	void updatePosY(float);
	float* calculatePlayerPosition();
	void updatePlayerVertices(float*);
	void fireEngines();
};

