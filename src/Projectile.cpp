#include "Projectile.h"
#include "Manager.h"

Projectile::Projectile(int type, float x, float y, float z)
	: Entity(type, x, y, z)
{
	Manager::addEntity(this);
}

Projectile::~Projectile()
{
}

// projectiles only move horizontally only, within bounds
void Projectile::updateXPosition(float x)
{
	// TODO destroy me when I hit let edge of screen
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
