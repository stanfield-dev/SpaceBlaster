#include <GL/glew.h>
#include <GLFW/glfw3.h>

#include <iostream>

#include "Enemy.h"
#include "VertexBuffers.h"

Enemy::Enemy()
{
	// arbitary starting position defaults
	m_enemyPosX = 0.5f;
	m_enemyPosY = 0.3f;
}

Enemy::~Enemy()
{
}

float Enemy::getPosX()
{
	return m_enemyPosX;
}

float Enemy::getPosY()
{
	return m_enemyPosY;
}

void Enemy::setPosX(float x)
{
	m_enemyPosX = x;
}

void Enemy::setPosY(float y)
{
	m_enemyPosY = y;
}

void Enemy::updatePosX(float x)
{
	m_enemyPosX += x;
}

void Enemy::updatePosY(float y)
{
	m_enemyPosY += y;
}

void Enemy::init()
{
	m_enemyVertices[0] = m_enemyPosX;					// quad LL
	m_enemyVertices[1] = m_enemyPosY;
	m_enemyVertices[2] = 0.0f;							// text LL
	m_enemyVertices[3] = 0.0f;	
	m_enemyVertices[4] = (float)ENEMY;					// text ID

	m_enemyVertices[5] = m_enemyPosX + m_xOffset;		// quad LR
	m_enemyVertices[6] = m_enemyPosY;
	m_enemyVertices[7] = 1.0f;
	m_enemyVertices[8] = 0.0f;
	m_enemyVertices[9] = (float)ENEMY;

	m_enemyVertices[10] = m_enemyPosX + m_xOffset;		// quad UR
	m_enemyVertices[11] = m_enemyPosY + m_yOffset;
	m_enemyVertices[12] = 1.0f;
	m_enemyVertices[13] = 1.0f;
	m_enemyVertices[14] = (float)ENEMY;

	m_enemyVertices[15] = m_enemyPosX;					// quad UL
	m_enemyVertices[16] = m_enemyPosY + m_yOffset;
	m_enemyVertices[17] = 0.0f;
	m_enemyVertices[18] = 1.0f;
	m_enemyVertices[19] = (float)ENEMY;

	updateEnemyVertices(m_enemyVertices);
}

void Enemy::updateEnemyVertices(float* enemyVertices)
{
	VertexBuffers::updateVertices(ENEMY, enemyVertices);
}

float* Enemy::calculateEnemyPosition()
{
	float newPosX = getPosX();

	if ((newPosX + m_xOffset) >= 1.0f) {
		newPosX = -1.0f;
		setPosX(-1.0f);
	}

	float newPosY = getPosY();

	if ((newPosY + m_yOffset) >= 1.0f) {
		newPosY = -1.0f;
		setPosY(-1.0f);
	}

	m_enemyVertices[0] = newPosX;					// quad LL
	m_enemyVertices[1] = newPosY;

	m_enemyVertices[5] = newPosX + m_xOffset;		// quad LR
	m_enemyVertices[6] = newPosY;

	m_enemyVertices[10] = newPosX + m_xOffset;		// quad UR
	m_enemyVertices[11] = newPosY + m_yOffset;

	m_enemyVertices[15] = newPosX;					// quad UL
	m_enemyVertices[16] = newPosY + m_yOffset;

	return m_enemyVertices;
}









