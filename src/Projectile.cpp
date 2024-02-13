#include "Projectile.h"
#include "EntityManager.h"

Projectile::Projectile(int type, float x, float y, float z, int projectileSource)
	: Entity(type, x, y, z)
{
	m_displayWidth = 64.0f;
	m_displayHeight = 32.0f;
	m_positionXOffset = m_displayWidth / SCREENWIDTH;
	m_positionYOffset = m_displayHeight / SCREENHEIGHT;

	m_positionY = y - (m_positionYOffset / 2.0f);  // center projectile on gun

	m_spriteSheetWidth = 256.0f;
	m_spriteSheetHeight = 64.0f;
	m_spriteWidth = 128.0f;
	m_spriteHeight = 64.0f;
	m_spriteXOffset = m_spriteWidth / m_spriteSheetWidth;
	m_spriteYOffset = m_spriteHeight / m_spriteSheetHeight;

	m_projectileSource = projectileSource;

	if (projectileSource == ENEMY) {
		m_spriteX = m_spriteXOffset;
	}

	updateVertexArray();

	EntityManager::addEntityToRegistry(this);
}

Projectile::~Projectile()
{
}


