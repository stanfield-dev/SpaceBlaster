#pragma once

static class IndexBuffer
{
private:
	static inline unsigned int m_indices[24] = {
	0, 1, 2, 2, 3, 0,
	4, 5, 6, 6, 7, 4,
	8, 9, 10, 10, 11, 8,
	12, 13, 14, 14, 15, 12
	};

	static inline unsigned int m_indexbufferID = 0;

public:
	IndexBuffer();
	~IndexBuffer();

	static void bindIBO();
	static void unbindIBO();
};