#pragma once

#include <GL/glew.h>

#include "defines.h"
#include "Entity.h"

#include "vector"

static class Renderer 
{
private:

public:
	static void init();
	static void drawEntities(unsigned int, std::vector<Entity*>);
};

