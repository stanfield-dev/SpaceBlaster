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
	if (m_indexbufferID == 0) {
		glGenBuffers(1, &m_indexbufferID);
	}
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_indexbufferID);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, 24 * sizeof(unsigned int), m_indices, GL_STATIC_DRAW);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_indexbufferID);
}

void IndexBuffer::unbindIBO()
{
	glDeleteBuffers(1, &m_indexbufferID);
}
