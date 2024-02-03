#pragma once

#include "defines.h"

static class Background
{
private:
	static inline float m_backgroundVertices[20];

public:
	static void init();
	static void scrollBackground();
};
