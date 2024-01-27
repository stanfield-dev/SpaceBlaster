#pragma once

#include <GL/glew.h>

#include "defines.h"

static class Renderer 
{
private:

public:
	Renderer();
	~Renderer();

	static void init();
	static void draw();
};

