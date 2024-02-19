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

	if (projectileSource == ENEMY) {
		m_spriteX = m_spriteXOffset;
	}

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

	if (projectileSource == ENEMY) {
		m_spriteX = m_spriteXOffset;
		rotateProjectile();
	}

	updateVertexArray();

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
}

void Projectile::rotateProjectile()
{
	m_modelMatrix = glm::mat4(1.0f);

	glm::mat4 fwdTranslate = glm::translate(glm::mat4(1.0f), glm::vec3(m_positionX + (m_positionXOffset / 2), m_positionY + (m_positionYOffset /2), 0.0f));
	glm::mat4 inverseTranslate = glm::inverse(fwdTranslate);
	glm::mat4 rotationMatrix = glm::rotate(glm::mat4(1.0f), m_radiansSourceToTarget, glm::vec3(0.0f, 0.0f, 1.0f));
	
	m_modelMatrix = fwdTranslate * rotationMatrix * inverseTranslate;

	glm::vec4 result = m_modelMatrix * glm::vec4(m_positionX, m_positionY, 0.0f, 1.0f);

	m_positionX = result.x;
	m_positionY = result.y;
}


