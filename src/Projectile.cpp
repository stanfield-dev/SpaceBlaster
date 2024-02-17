#include "Projectile.h"
#include "EntityManager.h"

Projectile::Projectile(int type, float x, float y, float z, int projectileSource)
	: Entity(type, x, y, z)
{
	m_displayWidth = PROJECTILEWIDTH;
	m_displayHeight = PROJECTILEHEIGHT;
	m_positionXOffset = m_displayWidth / SCREENWIDTH;
	m_positionYOffset = m_displayHeight / SCREENHEIGHT;

	m_positionY = y - (m_positionYOffset / 2.0f);  // center projectile sprite on gun

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

// overload for enemy AI to support auto-targetting the player
Projectile::Projectile(int type, float x, float y, float z, int projectileSource,
	float* sourceCoordinates, float* targetCoordinates)
	: Entity(type, x, y, z)
{
	m_displayWidth = PROJECTILEWIDTH;
	m_displayHeight = PROJECTILEHEIGHT;
	m_positionXOffset = m_displayWidth / SCREENWIDTH;
	m_positionYOffset = m_displayHeight / SCREENHEIGHT;

	m_positionY = y - (m_positionYOffset / 2.0f);  // center projectile sprite on gun

	m_spriteSheetWidth = 256.0f;
	m_spriteSheetHeight = 64.0f;
	m_spriteWidth = 128.0f;
	m_spriteHeight = 64.0f;
	m_spriteXOffset = m_spriteWidth / m_spriteSheetWidth;
	m_spriteYOffset = m_spriteHeight / m_spriteSheetHeight;

	m_projectileSource = projectileSource;
	m_projectileSourceCoordinates[0] = sourceCoordinates[0];
	m_projectileSourceCoordinates[1] = sourceCoordinates[1];
	m_projectileTargetCoordinates[0] = targetCoordinates[0];
	m_projectileTargetCoordinates[1] = targetCoordinates[1];

	if (projectileSource == ENEMY) {
		m_spriteX = m_spriteXOffset;
	}

	updateVertexArray();

	EntityManager::addEntityToRegistry(this);
}

Projectile::~Projectile()
{
}


