#pragma once

#include "defines.h"

static class Terrain
{
private:
	static inline float m_terrainVertices[20] = {
	 -1.0f, -1.0f,
	 0.0f, 0.0f,
	 (float)TERRAIN,

	 1.0f, -1.0f,
	 1.0f, 0.0f,
	 (float)TERRAIN,

	 1.0f, -0.8f,
	 1.0f, 1.0f,
	 (float)TERRAIN,

	 -1.0f, -0.8f,
	 0.0f, 1.0f,
	 (float)TERRAIN,
	};

public:
	static void init();
};
