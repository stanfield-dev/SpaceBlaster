#include "GL/glew.h"

#include "IndexBuffer.h"

IndexBuffer::IndexBuffer()
{
}

IndexBuffer::~IndexBuffer()
{
	glDeleteBuffers(1, &m_indexbufferID);
}

void IndexBuffer::createIndexBuffer(unsigned int* data, unsigned int count)
{
	glGenBuffers(1, &m_indexbufferID);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_indexbufferID);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, count * sizeof(unsigned int), data, GL_STATIC_DRAW);
}

void IndexBuffer::bindBuffer()
{
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_indexbufferID);
}

void IndexBuffer::unbindBuffer()
{
	glDeleteBuffers(1, &m_indexbufferID);
}
