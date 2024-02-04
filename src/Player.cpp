#include <GL/glew.h>
#include <GLFW/glfw3.h>

#include <iostream>

#include "Player.h"
#include "VertexBuffers.h"

Player::Player()
{
}

Player::~Player()
{
}

float Player::getPosX() const
{
	return m_playerPosX;
}

float Player::getPosY() const
{
	return m_playerPosY;
}

void Player::setPosX(float x)
{
	m_playerPosX = x;
}

void Player::setPosY(float y)
{
	m_playerPosY = y;
}

float Player::getGunPosition() const
{
	return m_playerPosY + (m_yOffset / 2);
}

//void Player::updatePosX(float x)
//{
//	if (x > 0.0f) {
//		if (m_playerPosX + m_xOffset + x >= 1.0f) {
//			m_playerPosX -= x;
//		}
//		else {
//			m_playerPosX += x;
//		}
//	}
//
//	if (x < 0.0f) {
//		if (m_playerPosX + x <= -1.0f) {
//			m_playerPosX = -1.0f;
//		}
//		else {
//			m_playerPosX += x;
//		}
//	}
//
//	calculatePlayerPosition();
//}

void Player::updatePosY(float y)
{
	if (y > 0.0f) {
		if (m_playerPosY + m_yOffset + y < 0.98f) {
			m_playerPosY += y;
		}
	}

	if (y < 0.0f) {
		if (m_playerPosY + y >= -0.85f) {
			m_playerPosY += y;
		}
	}

	calculatePlayerPosition();
}

void Player::init()
{
	m_playerVertices[0] = m_playerPosX;					// quad LL
	m_playerVertices[1] = m_playerPosY;
	m_playerVertices[2] = m_spriteXOrigin;				// text LL
	m_playerVertices[3] = m_spriteYOrigin;
	m_playerVertices[4] = (float)PLAYER;				// text ID

	m_playerVertices[5] = m_playerPosX + m_xOffset;		// quad LR
	m_playerVertices[6] = m_playerPosY;
	m_playerVertices[7] = m_spriteXOrigin + m_spriteXOffset;
	m_playerVertices[8] = m_spriteYOrigin;
	m_playerVertices[9] = (float)PLAYER;

	m_playerVertices[10] = m_playerPosX + m_xOffset;	// quad UR
	m_playerVertices[11] = m_playerPosY + m_yOffset;
	m_playerVertices[12] = m_spriteXOrigin + m_spriteXOffset;
	m_playerVertices[13] = m_spriteYOrigin + m_spriteYOffset;
	m_playerVertices[14] = (float)PLAYER;

	m_playerVertices[15] = m_playerPosX;				// quad UL
	m_playerVertices[16] = m_playerPosY + m_yOffset;
	m_playerVertices[17] = m_spriteXOrigin;
	m_playerVertices[18] = m_spriteYOrigin + m_spriteYOffset;
	m_playerVertices[19] = (float)PLAYER;

	updatePlayerVertices(m_playerVertices);
}

void Player::updatePlayerVertices(float *playerVertices)
{
	VertexBuffers::updateVertices(PLAYER, playerVertices);
}

float* Player::calculatePlayerPosition() {
	float newPosX = getPosX();

	if ((newPosX + m_xOffset) > 1.0f) {
		newPosX = -1.0f;
		setPosX(-1.0f);
	}

	else if ((newPosX + m_xOffset) < -1.0f) {
		newPosX = 1.0f - m_xOffset;
		setPosX(1.0f - m_xOffset);
	}

	float newPosY = getPosY();

	if ((newPosY + m_yOffset) > 1.0f) {
		newPosY = -1.0f;
		setPosY(-1.0f);
	}

	else if ((newPosY + m_yOffset) < -1.0f) {
		newPosY = 1.0f - m_yOffset;
		setPosY(1.0f - m_yOffset);
	}

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

void Player::fireEngines()
{
	if (m_spriteXOrigin + m_spriteXOffset >= 1.0f) {
		m_spriteXOrigin = 0.0f;
	}
	else {
		m_spriteXOrigin += m_spriteXOffset;
	}

	m_playerVertices[2] = m_spriteXOrigin;						// LLx
	m_playerVertices[7] = m_spriteXOrigin + m_spriteXOffset;	// LRx
	m_playerVertices[12] = m_spriteXOrigin + m_spriteXOffset;	// URx
	m_playerVertices[17] = m_spriteXOrigin;						// ULx

	updatePlayerVertices(m_playerVertices);
}





