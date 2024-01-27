#pragma once

#include <GL/glew.h>

#include "defines.h"

class Renderer 
{
private:

public:
	Renderer();
	~Renderer();

	void init();
	void draw();
};

