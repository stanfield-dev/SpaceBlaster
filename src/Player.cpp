#include <GL/glew.h>
#include <GLFW/glfw3.h>

#include <iostream>

#include "defines.h"
#include "Player.h"

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

void Player::updatePlayerVertices(float *m_coordinates)
{
	unsigned int vertexbuffer;
	glGenBuffers(1, &vertexbuffer);
	glBindBuffer(GL_ARRAY_BUFFER, vertexbuffer);
	glBufferData(GL_ARRAY_BUFFER, 16 * sizeof(float), m_coordinates, GL_STATIC_DRAW);
	glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 4 * sizeof(float), 0);
	glEnableVertexAttribArray(0);
	glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 4 * sizeof(float), (void*)(2 * sizeof(float)));
	glEnableVertexAttribArray(1);

	// DEBUGGERY
	//for (int x = 0; x < sizeof(m_coordinates) - 1; x++) {
	//	std::cout << "X[" << x << "]: " <<m_coordinates[x] << std::endl;
	//}

}

float* Player::calculatePlayerPosition() {
	float newPosX = getPosX();
	float newPosY = getPosY();

	// SHIP

	m_coordinates[0] = newPosX;										// quad LL
	m_coordinates[1] = newPosY;
	m_coordinates[2] = 0.0f;										// texture LL
	m_coordinates[3] = 0.0f;

	m_coordinates[4] = newPosX + (PLAYERWIDTH / SCREENWIDTH);		// quad LR
	m_coordinates[5] = newPosY;
	m_coordinates[6] = 1.0f;										// texture LR
	m_coordinates[7] = 0.0f;

	m_coordinates[8] = newPosX + (PLAYERWIDTH / SCREENWIDTH);		// quad UR
	m_coordinates[9] = newPosY + (PLAYERHEIGHT / SCREENHEIGHT);
	m_coordinates[10] = 1.0f;										// texture UR
	m_coordinates[11] = 1.0f;

	m_coordinates[12] = newPosX;									//quad UL
	m_coordinates[13] = newPosY + (PLAYERHEIGHT / SCREENHEIGHT);
	m_coordinates[14] = 0.0f;										// texture UL
	m_coordinates[15] = 1.0f;

	return m_coordinates;
}

void Player::setShaderID(unsigned int id)
{
	m_shaderID = id;
}

unsigned int Player::getShaderID()
{
	return m_shaderID;
}




