#pragma once

#include "EntityManager.h"
#include "Entity.h"

class Score : public Entity
{
private:
	int m_score = 0;

	float m_positionX1 = 0.0f; 
	float m_positionX2 = 0.0f;

	unsigned int m_VAO, m_vertexbufferID, m_indexbufferID;

	unsigned int m_iboIndices[18] = {
		0, 1, 2, 2, 3, 0,
		4, 5, 6, 6, 7, 4, 
		8, 9, 10, 10, 11, 8
	};

	float m_vertexScoreArray[72] = {
		// 100's
		m_positionX, 
		m_positionY, 
		m_positionZ, 
		m_spriteX, 
		m_spriteY, 
		(float)m_type,

		m_positionX + m_positionXOffset, 
		m_positionY, 
		m_positionZ, 
		m_spriteX + m_spriteXOffset, 
		m_spriteY, 
		(float)m_type,

		m_positionX + m_positionXOffset, 
		m_positionY + m_positionYOffset, 
		m_positionZ, 
		m_spriteX + m_spriteXOffset, 
		m_spriteY + m_spriteYOffset, 
		(float)m_type,

		m_positionX, 
		m_positionY + m_positionYOffset, 
		m_positionZ, 
		m_spriteX, 
		m_spriteY + m_spriteYOffset, 
		(float)m_type,

		// 10's
		m_positionX1,
		m_positionY,
		m_positionZ,
		m_spriteX,
		m_spriteY,
		(float)m_type,

		m_positionX1 + m_positionXOffset,
		m_positionY,
		m_positionZ,
		m_spriteX + m_spriteXOffset,
		m_spriteY,
		(float)m_type,

		m_positionX1 + m_positionXOffset,
		m_positionY + m_positionYOffset,
		m_positionZ,
		m_spriteX + m_spriteXOffset,
		m_spriteY + m_spriteYOffset,
		(float)m_type,

		m_positionX1,
		m_positionY + m_positionYOffset,
		m_positionZ,
		m_spriteX,
		m_spriteY + m_spriteYOffset,
		(float)m_type,

		// 1's
		m_positionX2,
		m_positionY,
		m_positionZ,
		m_spriteX,
		m_spriteY,
		(float)m_type,

		m_positionX2 + m_positionXOffset,
		m_positionY,
		m_positionZ,
		m_spriteX + m_spriteXOffset,
		m_spriteY,
		(float)m_type,

		m_positionX2 + m_positionXOffset,
		m_positionY + m_positionYOffset,
		m_positionZ,
		m_spriteX + m_spriteXOffset,
		m_spriteY + m_spriteYOffset,
		(float)m_type,

		m_positionX2,
		m_positionY + m_positionYOffset,
		m_positionZ,
		m_spriteX,
		m_spriteY + m_spriteYOffset,
		(float)m_type
	};

public:
	Score(int, float, float, float, EntityManager*);
	~Score();

	void generateBuffers() override;

	float* updateVertexArray() override;
	void updateVertexBuffer() override;
	void bindIBO() override;

	void updateScore() override;
};