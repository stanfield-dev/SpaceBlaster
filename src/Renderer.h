#pragma once

#include <GL/glew.h>

#include "defines.h"
#include "EntityManager.h"
#include "Entity.h"
#include "Shader.h"

#include "vector"

class Renderer 
{
private:
	enum m_gameState : int
	{
		NEW = 0,
		RUNNING,
		STARTSCREEN,
		HELPSCREEN,
		INTERMISSION,
		NEWROUND,
		GAMEOVER
	};

public:
	static void init(unsigned int);

	static void drawEntities(int, unsigned int, EntityManager*);

	static void drawInfoScreen(Entity*, unsigned int);
	static void drawGameScreen(EntityManager*, unsigned int);
};

