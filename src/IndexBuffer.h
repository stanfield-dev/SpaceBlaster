#pragma once

static class IndexBuffer
{
private:
	inline static unsigned int m_indexbufferID = 0;

public:
	IndexBuffer();
	~IndexBuffer();

	static void createIndexBuffer(unsigned int*, unsigned int);
	static void bindBuffer();
	static void unbindBuffer();
};