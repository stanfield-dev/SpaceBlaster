#include "Renderer.h"

#include "IndexBuffer.h"
#include "Textures.h"
#include "VertexBuffers.h"

Renderer::Renderer()
{
}

Renderer::~Renderer()
{
}

void Renderer::init()
{
	glClearColor(1.0f, 0.0f, 0.0f, 1.0f);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	glEnable(GL_BLEND);
}

void Renderer::draw()
{
	glClear(GL_COLOR_BUFFER_BIT);

	VertexBuffers::enableVAO();
	IndexBuffer::bindIBO();

	glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);

	IndexBuffer::unbindIBO();
	VertexBuffers::disableVAO();
}
