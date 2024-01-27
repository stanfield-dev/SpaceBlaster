#pragma once

static class IndexBuffer
{
private:
	static inline unsigned int m_vertexIndices[6] = {
	0, 1, 2,
	2, 3, 0
	};

	static inline unsigned int m_indexbufferID = 0;

public:
	IndexBuffer();
	~IndexBuffer();

	static void bindIBO();
	static void unbindIBO();
};