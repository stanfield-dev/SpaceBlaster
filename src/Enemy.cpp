#include "Enemy.h"

#include <math.h>
#include <time.h>

Enemy::Enemy(int type, float x, float y, float z, EntityManager* entityManager)
	: Entity(type, x, y, z)
{
	m_displayWidth = ENEMYWIDTH;
	m_displayHeight = ENEMYHEIGHT;
	m_positionXOffset = m_displayWidth / SCREENWIDTH;
	m_positionYOffset = m_displayHeight / SCREENHEIGHT;

	m_spriteSheetWidth = 4096.0f;
	m_spriteSheetHeight = 512.0f;
	m_spriteWidth = 512.0f;
	m_spriteHeight = 512.0f;
	m_spriteXOffset = m_spriteWidth / m_spriteSheetWidth;
	m_spriteYOffset = m_spriteHeight / m_spriteSheetHeight;

	srand((unsigned int)time(0));
	int randomDest = rand() % m_destinations.size();

	m_destinationX = m_destinations[randomDest].x;
	m_destinationY = m_destinations[randomDest].y;

	m_vectorSourceToTarget[0] = m_destinationX - m_positionX;
	m_vectorSourceToTarget[1] = m_destinationY - m_positionY;

	updateVertexArray();

	entityManager->addEntityToRegistry(this);
}

Enemy::~Enemy()
{
}

void Enemy::moveEnemy()
{
	float approxEqualX = std::abs(m_positionX - m_destinationX);
	float approxEqualY = std::abs(m_positionY - m_destinationY);

	if ((approxEqualX < 0.0001f) && (approxEqualY < 0.0001f)) {
		srand((unsigned int)time(0));
		int randomDest = rand() % m_destinations.size();

		m_destinationX = m_destinations[randomDest].x;
		m_destinationY = m_destinations[randomDest].y;

		m_vectorSourceToTarget[0] = m_destinationX - m_positionX;
		m_vectorSourceToTarget[1] = m_destinationY - m_positionY;
	}

	m_positionX += (m_vectorSourceToTarget[0] * m_enemyVelocity);
	m_positionY += (m_vectorSourceToTarget[1] * m_enemyVelocity);

	updateVertexArray();
}




