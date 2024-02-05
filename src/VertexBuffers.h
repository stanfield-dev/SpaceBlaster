#pragma once

static class VertexBuffers
{
private:
	const static int TOTALOBJECTS = 5;

	static inline unsigned int m_VAO;
	static inline unsigned int m_vertexbufferID;

public:
	VertexBuffers();
	~VertexBuffers();

	static void init();
	static void updateVertices(int, float*);
	static void enableVAO();
	static void disableVAO();
};

