#include "Renderer.h"

#include "IndexBuffer.h"
#include "Shader.h"
#include "Textures.h"
#include "VertexBuffers.h"

#include <iostream>

Renderer::Renderer()
{
}

Renderer::~Renderer()
{
}

void Renderer::init()
{
	glClearColor(0.0f, 0.2f, 0.1f, 1.0f);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	glEnable(GL_BLEND);
	glEnable(GL_DEPTH_TEST);
}

void Renderer::draw(unsigned int shaderProgram)
{
	glClear(GL_COLOR_BUFFER_BIT);

	Shader::useShader(shaderProgram);

	VertexBuffers::enableVAO();
	IndexBuffer::bindIBO();

	glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);

}
