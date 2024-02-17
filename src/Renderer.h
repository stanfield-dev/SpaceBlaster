#pragma once

#include <GL/glew.h>

#include "defines.h"
#include "EntityManager.h"
#include "Entity.h"
#include "Shader.h"

#include "vector"

static class Renderer 
{
private:

public:
	static void init();
	static void drawEntities(unsigned int, EntityManager*);
};

