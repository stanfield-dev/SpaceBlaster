#include "Projectile.h"
#include "EntityManager.h"

Projectile::Projectile(int type, float x, float y, float z, int projectileSource)
	: Entity(type, x, y, z)
{
	m_displayWidth = 128.0f;
	m_displayHeight = 11.0f;
	m_positionXOffset = m_displayWidth / SCREENWIDTH;
	m_positionYOffset = m_displayHeight / SCREENHEIGHT;

	m_spriteSheetWidth = 4096.0f;
	m_spriteSheetHeight = 512.0f;
	m_spriteWidth = 512.0f;
	m_spriteHeight = 512.0f;
	m_spriteXOffset = m_spriteWidth / m_spriteSheetWidth;
	m_spriteYOffset = m_spriteHeight / m_spriteSheetHeight;

	updateVertexArray();

	EntityManager::addEntityToRegistry(this);
}

Projectile::~Projectile()
{
}


