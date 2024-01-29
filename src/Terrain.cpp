#include "Terrain.h"
#include "VertexBuffers.h"

void Terrain::init()
{
	m_terrainVertices[0] = -1.0f;				// quad LL
	m_terrainVertices[1] = -1.0f;
	m_terrainVertices[2] =  0.0f;
	m_terrainVertices[3] =  0.0f;
	m_terrainVertices[4] = (float)TERRAIN;

	m_terrainVertices[5] =  1.0f;				// quad LR
	m_terrainVertices[6] = -1.0f;
	m_terrainVertices[7] =  1.0f;
	m_terrainVertices[8] =  0.0f;
	m_terrainVertices[9] = (float)TERRAIN;

	m_terrainVertices[10] =  1.0f;				// quad UR
	m_terrainVertices[11] = -0.8f;
	m_terrainVertices[12] =  1.0f;
	m_terrainVertices[13] =  1.0f;
	m_terrainVertices[14] = (float)TERRAIN;

	m_terrainVertices[15] = -1.0f;				// quad UL
	m_terrainVertices[16] = -0.8f;
	m_terrainVertices[17] =  0.0f;
	m_terrainVertices[18] =  1.0f;
	m_terrainVertices[19] = (float)TERRAIN;

	VertexBuffers::updateVertices(TERRAIN, m_terrainVertices);
}
