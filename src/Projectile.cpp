#include "Projectile.h"

Projectile::Projectile(int type, float x, float y, float z, int projectileSource, EntityManager* entityManager)
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

	updateVertexArray();

	entityManager->addEntityToRegistry(this);
}

// overload for enemy AI to support auto-targetting the player
Projectile::Projectile(int type, float x, float y, float z, int projectileSource,
	float* sourceCoordinates, float* targetCoordinates, EntityManager* entityManager)
	: Entity(type, x, y, z)
{
	m_displayWidth = PROJECTILEWIDTH;
	m_displayHeight = PROJECTILEHEIGHT;
	m_positionXOffset = m_displayWidth / SCREENWIDTH;
	m_positionYOffset = m_displayHeight / SCREENHEIGHT;

	m_positionY = y - (m_positionYOffset / 2.0f);  // center projectile sprite on gun
	m_positionX = x - (m_positionXOffset / 2.0f);
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

	m_vectorSourceToTarget[0] = m_projectileTargetCoordinates[0] - m_projectileSourceCoordinates[0];
	m_vectorSourceToTarget[1] = m_projectileTargetCoordinates[1] - m_projectileSourceCoordinates[1];

	m_radiansSourceToTarget = glm::atan((m_vectorSourceToTarget[1]) / m_vectorSourceToTarget[0]);

	m_spriteX = m_spriteXOffset;

	updateVertexArray();
	rotateProjectile();

	entityManager->addEntityToRegistry(this);
}

Projectile::~Projectile()
{
}

void Projectile::moveProjectile() 
{
	m_positionX += (m_vectorSourceToTarget[0] * m_projectileVelocity);
	m_positionY += (m_vectorSourceToTarget[1] * m_projectileVelocity);

	updateVertexArray();

	if (this->getProjectileSource() == ENEMY) {
		rotateProjectile();
	}
}

void Projectile::rotateProjectile()
{
	float c, s, originX, originY;

	c = cos(m_radiansSourceToTarget);
	s = sin(m_radiansSourceToTarget);

	originX = m_positionX + (m_positionXOffset / 2);
	originY = m_positionY + (m_positionYOffset / 2);

	for (int x = 0; x < 20; x += 6)
	{
		m_vertexArray[x]	= c * (m_vertexArray[x] - originX) - s * (m_vertexArray[x + 1] - originY) + originX;
		m_vertexArray[x + 1] = s * (m_vertexArray[x] - originX) + c * (m_vertexArray[x + 1] - originY) + originY;

	}
}


