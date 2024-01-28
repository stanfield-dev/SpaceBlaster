#include <GL/glew.h>
#include <GLFW/glfw3.h>

#include <iostream>

#include "Player.h"
#include "VertexBuffers.h"

Player::Player()
{
	// arbitary starting position defaults
	m_playerPosX = 0.0f;
	m_playerPosY = -0.9f;
}

Player::~Player()
{
}

float Player::getPosX()
{
	return m_playerPosX;
}

float Player::getPosY()
{
	return m_playerPosY;
}

void Player::updatePosX(float x)
{
	m_playerPosX += x;
}

void Player::updatePosY(float y)
{
	m_playerPosY += y;
}

void Player::init()
{
	m_playerVertices[0] = m_playerPosX;					// quad LL
	m_playerVertices[1] = m_playerPosY;
	m_playerVertices[2] = -1.0f;						// text LL
	m_playerVertices[3] = -1.0f;
	m_playerVertices[4] = (float)PLAYER;				// text ID

	m_playerVertices[5] = m_playerPosX + m_xOffset;		// quad LR
	m_playerVertices[6] = m_playerPosY;
	m_playerVertices[7] =  1.0f;
	m_playerVertices[8] = -1.0f;
	m_playerVertices[9] = (float)PLAYER;

	m_playerVertices[10] = m_playerPosX + m_xOffset;	// quad UR
	m_playerVertices[11] = m_playerPosY + m_yOffset;
	m_playerVertices[12] = 1.0f;
	m_playerVertices[13] = 1.0f;
	m_playerVertices[14] = (float)PLAYER;

	m_playerVertices[15] = m_playerPosX;				// quad UL
	m_playerVertices[16] = m_playerPosY + m_yOffset;
	m_playerVertices[17] = -1.0f;
	m_playerVertices[18] =  1.0f;
	m_playerVertices[19] = (float)PLAYER;

	updatePlayerVertices(m_playerVertices);
}

void Player::updatePlayerVertices(float *playerVertices)
{
	VertexBuffers::updateVertices(PLAYER, playerVertices);
}

float* Player::calculatePlayerPosition() {
	float newPosX = getPosX();
	float newPosY = getPosY();

	m_playerVertices[0] =  newPosX;					// quad LL
	m_playerVertices[1] =  newPosY;

	m_playerVertices[5] =  newPosX + m_xOffset;		// quad LR
	m_playerVertices[6] =  newPosY;

	m_playerVertices[10] = newPosX + m_xOffset;		// quad UR
	m_playerVertices[11] = newPosY + m_yOffset;

	m_playerVertices[15] = newPosX;					// quad UL
	m_playerVertices[16] = newPosY + m_yOffset;

	return m_playerVertices;
}





