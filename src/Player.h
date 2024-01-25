#pragma once
#include <string>
#include "stb_image.h"

class Player 
{
private:
	// arbitary starting position defaults
	float m_playerPosX;
	float m_playerPosY;
	float m_coordinates[16];

	unsigned int m_shaderID;

public:

	Player();
	~Player();

	float getPosX();
	float getPosY();

	void updatePosX(float);
	void updatePosY(float);
	void setShaderID(unsigned int);
	unsigned int getShaderID();
	float* calculatePlayerPosition();
	void updatePlayerVertices(float []);
};

