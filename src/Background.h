#pragma once

#include "defines.h"

static class Background
{
private:
	static inline float m_backgroundVertices[20] = {
		-1.0f, -1.0f,
		0.0f, 0.0f,
		(float)BACKGROUND,

		1.0f, -1.0f,
		1.0f, 0.0f,
		(float)BACKGROUND,

		1.0f, 1.0f,
		1.0f, 1.0f,
		(float)BACKGROUND,

		-1.0f, 1.0f,
		0.0f, 1.0f,
		(float)BACKGROUND,
	};

public:
	static void init();
	static void scrollBackground();
};
