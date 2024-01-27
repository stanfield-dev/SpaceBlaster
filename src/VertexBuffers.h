#pragma once

static class VertexBuffers
{
private:
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

