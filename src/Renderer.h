#pragma once

#include <GL/glew.h>

#include "defines.h"

class Renderer 
{
private:
	/*unsigned int m_bufferIDs[3];*/
	unsigned int indexBuffer;
	float background_coordinates[16];

	unsigned int m_vertexIndices[6] = {
		0, 1, 2,
		2, 3, 0
	};

	enum m_attributeIndex : unsigned int {
		INDEX = 0,
		TEXTURE,
		POSITION
	};

	struct m_attribLayout{
		int m_Size = 0;
		int m_Type = GL_FLOAT;
		unsigned int m_Stride = 0;
	};


	int getVerticeCount();
	void bindBuffers(unsigned int*);
	void freeBuffers(unsigned int*);
	void updateAttribArray(unsigned int);

public:
	Renderer();
	~Renderer();

	void init();
	void draw();
	void renderBackground(unsigned int);
};

