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
	static inline unsigned int m_projectionMatrixLoc = 0;
	static inline unsigned int m_viewMatrixLoc = 0;
	static inline unsigned int m_modelMatrixLoc = 0;

	static inline glm::mat4 m_projectionMatrix = glm::mat4(1.0f);
	static inline glm::mat4 m_viewMatrix = glm::mat4(1.0f);

public:
	static void init(unsigned int);
	static void drawEntities(unsigned int, EntityManager*);
};

