#include "Background.h"
#include "VertexBuffers.h"

void Background::init()
{
	m_backgroundVertices[0] = -1.0f;				// quad LL
	m_backgroundVertices[1] = -1.0f;
	m_backgroundVertices[2] = -1.0f;
	m_backgroundVertices[3] = -1.0f;
	m_backgroundVertices[4] = (float)BACKGROUND;

	m_backgroundVertices[5] =  1.0f;				// quad LR
	m_backgroundVertices[6] = -1.0f;
	m_backgroundVertices[7] =  1.0f;
	m_backgroundVertices[8] = -1.0f;
	m_backgroundVertices[9] = (float)BACKGROUND;

	m_backgroundVertices[10] = 1.0f;				// quad UR
	m_backgroundVertices[11] = 1.0f;
	m_backgroundVertices[12] = 1.0f;
	m_backgroundVertices[13] = 1.0f;
	m_backgroundVertices[14] = (float)BACKGROUND;

	m_backgroundVertices[15] = -1.0f;				// quad UL
	m_backgroundVertices[16] =  1.0f;
	m_backgroundVertices[17] = -1.0f;
	m_backgroundVertices[18] =  1.0f;
	m_backgroundVertices[19] = (float)BACKGROUND;

	VertexBuffers::updateVertices(BACKGROUND, m_backgroundVertices);
}
