#include "Renderer.h"

#include "IndexBuffer.h"
#include "Texture.h"

Renderer::Renderer()
{

}

Renderer::~Renderer()
{

}

void Renderer::init()
{
	glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	glEnable(GL_BLEND);

	IndexBuffer::createIndexBuffer(m_vertexIndices, 6);
}

void Renderer::draw()
{
	glDrawElements(GL_TRIANGLES, getVerticeCount(), GL_UNSIGNED_INT, 0);
}

int Renderer::getVerticeCount()
{
	return sizeof(m_vertexIndices) / 4;
}

void Renderer::bindBuffers(unsigned int* m_bufferIDs)
{
	//glBindBuffer(GL_ARRAY_BUFFER, m_bufferIDs[0]);  // vertexIndices
	//glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_bufferIDs[1]);  // texture coords
	//glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_bufferIDs[2]);  // position coords
}

void Renderer::freeBuffers(unsigned int* m_bufferIDs)
{
	glDeleteBuffers(3, m_bufferIDs);
}

void Renderer::updateAttribArray(unsigned int x)
{
}

void Renderer::renderBackground(unsigned int shaderProgram)
{
	background_coordinates[0] = -1.0f;										// quad LL
	background_coordinates[1] = -1.0f;
	background_coordinates[2] = 0.0f;										// texture LL
	background_coordinates[3] = 0.0f;

	background_coordinates[4] = 1.0f;										// quad LR
	background_coordinates[5] = -1.0f;
	background_coordinates[6] = 1.0f;										// texture LR
	background_coordinates[7] = 0.0f;

	background_coordinates[8] = 1.0f;										// quad UR
	background_coordinates[9] = 1.0f;
	background_coordinates[10] = 1.0f;										// texture UR
	background_coordinates[11] = 1.0f;

	background_coordinates[12] = -1.0f;										//quad UL
	background_coordinates[13] = 1.0f;
	background_coordinates[14] = 0.0f;										// texture UL
	background_coordinates[15] = 1.0f;

	unsigned int bg_vertexbuffer;
	glGenBuffers(1, &bg_vertexbuffer);
	glBindBuffer(GL_ARRAY_BUFFER, bg_vertexbuffer);
	glBufferData(GL_ARRAY_BUFFER, 16 * sizeof(float), background_coordinates, GL_STATIC_DRAW);
	glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 4 * sizeof(float), 0);
	glEnableVertexAttribArray(0);
	glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 4 * sizeof(float), (void*)(2 * sizeof(float)));
	glEnableVertexAttribArray(1);
	glBindBuffer(GL_ARRAY_BUFFER, 0);

	Texture::loadTexture(BACKGROUND_IMAGE, GL_TEXTURE_2D, shaderProgram);
}