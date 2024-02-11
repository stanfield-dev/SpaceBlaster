#include "Entity.h"

Entity::Entity(int type, float x, float y, float z)
	: m_type(type), m_positionX(x), m_positionY(y), m_positionZ(z)
{
	glGenVertexArrays(1, &m_VAO);
	glGenBuffers(1, &m_vertexbufferID);
	glGenBuffers(1, &m_indexbufferID);
}

Entity::~Entity()
{
	glDeleteBuffers(1, &m_indexbufferID);
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

float Entity::getGunPositionX() const
{
	return m_positionX + m_positionXOffset;
}

float Entity::getGunPositionY() const
{
	return m_positionY + (m_positionYOffset / 2);
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

void Entity::fireEngines()
{
	if (m_spriteX + m_spriteXOffset >= 1.0f) {
		m_spriteX = 0.0f;
	}
	else {
		m_spriteX += m_spriteXOffset;
	}

	m_vertexArray[3] = m_spriteX;						// LLx
	m_vertexArray[9] = m_spriteX + m_spriteXOffset;		// LRx
	m_vertexArray[15] = m_spriteX + m_spriteXOffset;	// URx
	m_vertexArray[21] = m_spriteX;						// ULx

	updateVertexArray();
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




