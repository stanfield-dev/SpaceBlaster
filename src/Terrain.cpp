#include "Terrain.h"
#include "VertexBuffers.h"

void Terrain::init()
{
	VertexBuffers::updateVertices(TERRAIN, m_terrainVertices);
}
