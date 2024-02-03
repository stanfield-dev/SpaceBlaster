#include "Background.h"
#include "VertexBuffers.h"

void Background::init()
{
	m_backgroundVertices[0] = -1.0f;				// quad LL
	m_backgroundVertices[1] = -1.0f;
	m_backgroundVertices[2] =  0.0f;
	m_backgroundVertices[3] =  0.0f;
	m_backgroundVertices[4] = (float)BACKGROUND;

	m_backgroundVertices[5] =  1.0f;				// quad LR
	m_backgroundVertices[6] = -1.0f;
	m_backgroundVertices[7] =  1.0f;
	m_backgroundVertices[8] =  0.0f;
	m_backgroundVertices[9] = (float)BACKGROUND;

	m_backgroundVertices[10] = 1.0f;				// quad UR
	m_backgroundVertices[11] = 1.0f;
	m_backgroundVertices[12] = 1.0f;
	m_backgroundVertices[13] = 1.0f;
	m_backgroundVertices[14] = (float)BACKGROUND;

	m_backgroundVertices[15] = -1.0f;				// quad UL
	m_backgroundVertices[16] =  1.0f;
	m_backgroundVertices[17] =  0.0f;
	m_backgroundVertices[18] =  1.0f;
	m_backgroundVertices[19] = (float)BACKGROUND;

	VertexBuffers::updateVertices(BACKGROUND, m_backgroundVertices);
}

void Background::scrollBackground()
{
	m_backgroundVertices[2] += 0.002f;				// LLx
	m_backgroundVertices[7] += 0.002f;				// LRx
	m_backgroundVertices[12] += 0.002f;				// URx
	m_backgroundVertices[17] += 0.002f;				// ULx

	VertexBuffers::updateVertices(BACKGROUND, m_backgroundVertices);
}
