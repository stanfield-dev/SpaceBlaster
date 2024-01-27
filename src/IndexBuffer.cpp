#include "GL/glew.h"

#include "IndexBuffer.h"

IndexBuffer::IndexBuffer()
{
}

IndexBuffer::~IndexBuffer()
{
}

void IndexBuffer::bindIBO()
{
	glGenBuffers(1, &m_indexbufferID);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_indexbufferID);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, 6 * sizeof(unsigned int), m_vertexIndices, GL_STATIC_DRAW);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_indexbufferID);
}

void IndexBuffer::unbindIBO()
{
	glDeleteBuffers(1, &m_indexbufferID);
}
