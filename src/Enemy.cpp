#include <GL/glew.h>
#include <GLFW/glfw3.h>

#include "Enemy.h"
#include "Manager.h"

Enemy::Enemy(int type, float x, float y, float z)
	: Entity(type, x, y, z)
{
	Manager::addEntity(this);
}

Enemy::~Enemy()
{
}

void Enemy::updateXPosition(float x)
{
	if (x > 0.0f) {
		if (m_positionX + m_positionXOffset + x >= 1.0f) {
			m_positionX -= x;
		}
		else {
			m_positionX += x;
		}
	}

	if (x < 0.0f) {
		if (m_positionX + x <= -1.0f) {
			m_positionX = -1.0f;
		}
		else {
			m_positionX += x;
		}
	}
}

void Enemy::updateYPosition(float y)
{
	float topBound = 0.98f;
	float bottomBound = -0.85f;

	if (y > 0.0f) {
		if (m_positionY + m_positionYOffset + y < topBound) {
			m_positionY += y;
		}
	}

	if (y < 0.0f) {
		if (m_positionY + y >= bottomBound) {
			m_positionY += y;
		}
	}
}
