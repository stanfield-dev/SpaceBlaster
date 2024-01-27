#pragma once

#include "defines.h"

class Player 
{
private:
	float m_xOffset = PLAYERWIDTH / SCREENWIDTH;
	float m_yOffset = PLAYERHEIGHT / SCREENHEIGHT;
	float m_playerPosX;
	float m_playerPosY;
	float m_playerVertices[20];

public:

	Player();
	~Player();

	float getPosX();
	float getPosY();

	void init();
	void updatePosX(float);
	void updatePosY(float);
	float* calculatePlayerPosition();
	void updatePlayerVertices(float []);
};

