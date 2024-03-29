#include "Entity.h"

#include <iostream>

Entity::Entity(int type, float x, float y, float z)
	: m_type(type), m_positionX(x), m_positionY(y), m_positionZ(z)
{
	generateBuffers();
}

Entity::~Entity()
{
	unbindVAO();
	glDeleteBuffers(1, &m_indexbufferID);
	glDeleteBuffers(1, &m_vertexbufferID);
}

void Entity::animateCountdown() {}
int Entity::getCountdownFrame() const { return 0; }
void Entity::animateExplosion() {}
int Entity::getExplosionFrame() const { return 0; }
void Entity::animateScreen() {}
void Entity::animateShip() {}

void Entity::updateHealthBarLives(int) {}

void Entity::updateScore() {}

void Entity::moveEnemy() {}
void Entity::moveProjectile() {}

void Entity::increaseDifficulty(float) {}
float Entity::getDifficultyLevel() { return 0.0f; }

void Entity::generateBuffers()
{
	glGenVertexArrays(1, &m_VAO);
	glGenBuffers(1, &m_vertexbufferID);
	glGenBuffers(1, &m_indexbufferID);
}

int Entity::getType() const
{
	return m_type;
}

float Entity::getPositionX() const
{
	return m_positionX;
}

float Entity::getPositionY() const
{
	return m_positionY;
}

float Entity::getPositionZ() const
{
	return m_positionZ;
}

float* Entity::getProjectileTargetPosition() 
{
	Entity::m_gunPosition position = getGunPosition();

	m_projectileTargetCoordinates[0] = position.x;
	m_projectileTargetCoordinates[1] = position.y;

	return m_projectileTargetCoordinates;
}

float* Entity::getProjectileSourcePosition() 
{
	Entity::m_gunPosition position = getGunPosition();

	m_projectileSourceCoordinates[0] = position.x;
	m_projectileSourceCoordinates[1] = position.y;

	return m_projectileSourceCoordinates;
}

m_boundingBox Entity::boundingBox() const
{
	m_boundingBox box = { 0.0f, 0.0f, 0.0f, 0.0f };

	box.left	= m_positionX;
	box.right	= m_positionX + m_positionXOffset;
	box.top		= m_positionY + m_positionYOffset;
	box.bottom	= m_positionY;

	return box;
}

Entity::m_gunPosition Entity::getGunPosition() const
{
	m_gunPosition position = { 0.0f, 0.0f };
	
	if (this->m_type == PLAYER) {
		position.x = m_positionX + m_positionXOffset;
	}
	else {
		position.x = m_positionX;
	}
	position.y = m_positionY + (m_positionYOffset / 2);

	return position;
}

void Entity::setPositionX(float x)
{
	m_positionX = x;
}

void Entity::setPositionY(float y)
{
	m_positionY = y;
}

void Entity::updatePositionX(float x)
{
	m_positionX += x;
	updateVertexArray();
}

void Entity::updatePositionY(float y)
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

	updateVertexArray();
}

int Entity::getProjectileSource() const
{
	return m_projectileSource;
}

int Entity::getCountdownSource() const
{
	return m_countdownSource;
}

float* Entity::updateVertexArray()
{
	float newPosX = getPositionX();
	float newPosY = getPositionY();

	m_vertexArray[0] = newPosX;							// quad LL
	m_vertexArray[1] = newPosY;
	m_vertexArray[2] = m_positionZ;
	m_vertexArray[3] = m_spriteX;						// texture LL
	m_vertexArray[4] = m_spriteY;

	m_vertexArray[6] = newPosX + m_positionXOffset;		// LR
	m_vertexArray[7] = newPosY;
	m_vertexArray[8] = m_positionZ;
	m_vertexArray[9] = m_spriteX + m_spriteXOffset;
	m_vertexArray[10] = m_spriteY;

	m_vertexArray[12] = newPosX + m_positionXOffset;	// UR
	m_vertexArray[13] = newPosY + m_positionYOffset;
	m_vertexArray[14] = m_positionZ;
	m_vertexArray[15] = m_spriteX + m_spriteXOffset;
	m_vertexArray[16] = m_spriteY + m_spriteYOffset;

	m_vertexArray[18] = newPosX;						// UL
	m_vertexArray[19] = newPosY + m_positionYOffset;
	m_vertexArray[20] = m_positionZ;
	m_vertexArray[21] = m_spriteX;
	m_vertexArray[22] = m_spriteY + m_spriteYOffset;

	return m_vertexArray;
}

void Entity::updateVertexBuffer()
{
	int numberOfVertices = 24;
	int sizeOfBuffer = numberOfVertices * sizeof(float);

	glBindBuffer(GL_ARRAY_BUFFER, m_vertexbufferID);
	glBufferData(GL_ARRAY_BUFFER, sizeOfBuffer, (const void*)m_vertexArray, GL_DYNAMIC_DRAW);
	glEnableVertexAttribArray(0);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), 0);
	glEnableVertexAttribArray(1);
	glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (const void*)(3 * sizeof(float)));
	glEnableVertexAttribArray(2);
	glVertexAttribPointer(2, 1, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (const void*)(5 * sizeof(float)));
}

void Entity::bindVAO()
{
	glBindVertexArray(m_VAO);
}

void Entity::unbindVAO()
{
	glBindVertexArray(0);
}

void Entity::bindIBO()
{
	int numberOfIBOIndices = 6;

	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_indexbufferID);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, numberOfIBOIndices * sizeof(unsigned int), m_iboIndices, GL_STATIC_DRAW);
}




