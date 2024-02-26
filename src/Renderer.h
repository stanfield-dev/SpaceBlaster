#pragma once

#include <GL/glew.h>

#include "sb_defines.h"

#include "EntityManager.h"
#include "Entity.h"
#include "Shader.h"

#include "vector"

class Renderer 
{
private:

public:
	static void init(unsigned int);

	static void drawEntities(int, unsigned int, EntityManager*);

	static void drawInfoScreen(Entity*, unsigned int);
	static void drawGameScreen(EntityManager*, unsigned int);
	static void drawGameCountdownScreen(EntityManager*, unsigned int);
	static void drawGameOverScreen(EntityManager*, unsigned int);
	static void drawScore(EntityManager*, unsigned int);
};

