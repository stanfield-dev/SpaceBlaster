#include <GL/glew.h>
#include <GLFW/glfw3.h>

#include "Player.h"
#include "Manager.h"

Player::Player(int type, float x, float y, float z)
	: Entity(type, x, y, z)
{
	Manager::addEntity(this);
}

Player::~Player()
{
}

// player ship moves up and down only, within bounds
void Player::updateYPosition(float y)
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






