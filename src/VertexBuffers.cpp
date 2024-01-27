#include <GL/glew.h>

#include "defines.h"
#include "VertexBuffers.h"

#include <iostream>

VertexBuffers::VertexBuffers()
{
}

VertexBuffers::~VertexBuffers()
{
}

void VertexBuffers::init()
{
	glGenVertexArrays(1, &m_VAO);
	enableVAO();
	glGenBuffers(1, &m_vertexbufferID);
}

void VertexBuffers::updateVertices(int type, float* vertices)
{
	unsigned int size = 4 * 20 * sizeof(float);	// # objects * elements per objects * 4 bytes
	unsigned int offset = type * (size/4);

	glBindBuffer(GL_ARRAY_BUFFER, m_vertexbufferID);
	glBufferData(GL_ARRAY_BUFFER, size, NULL, GL_DYNAMIC_DRAW);
	glNamedBufferSubData(m_vertexbufferID, offset, size / 4, vertices);

	glEnableVertexAttribArray(0);
	glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 5 * sizeof(float), 0);
	glEnableVertexAttribArray(1);
	glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (const void*)(2 * sizeof(float)));
	glEnableVertexAttribArray(2);
	glVertexAttribPointer(2, 1, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (const void*)(4 * sizeof(float)));

}

void VertexBuffers::enableVAO()
{
	glBindVertexArray(m_VAO);
}

void VertexBuffers::disableVAO()
{
	glBindVertexArray(0);
}


