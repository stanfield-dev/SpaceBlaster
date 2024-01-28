#include "Terrain.h"
#include "VertexBuffers.h"

void Terrain::init()
{
	m_terrainVertices[0] = -0.1f;				// quad LL
	m_terrainVertices[1] = -1.0f;
	m_terrainVertices[2] = -1.0f;
	m_terrainVertices[3] = -1.0f;
	m_terrainVertices[4] = (float)TERRAIN;

	m_terrainVertices[5] = 0.1f;				// quad LR
	m_terrainVertices[6] = -1.0f;
	m_terrainVertices[7] = 1.0f;
	m_terrainVertices[8] = -1.0f;
	m_terrainVertices[9] = (float)TERRAIN;

	m_terrainVertices[10] = 0.1f;				// quad UR
	m_terrainVertices[11] = -0.9f;
	m_terrainVertices[12] = 1.0f;
	m_terrainVertices[13] = 1.0f;
	m_terrainVertices[14] = (float)TERRAIN;

	m_terrainVertices[15] = -0.1f;				// quad UL
	m_terrainVertices[16] = -0.9f;
	m_terrainVertices[17] = -1.0f;
	m_terrainVertices[18] = 1.0f;
	m_terrainVertices[19] = (float)TERRAIN;

	VertexBuffers::updateVertices(TERRAIN, m_terrainVertices);
}
