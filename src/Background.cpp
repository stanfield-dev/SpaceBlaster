#include "Background.h"
#include "VertexBuffers.h"

void Background::init()
{
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
