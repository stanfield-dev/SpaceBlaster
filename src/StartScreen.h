#pragma once

#include "EntityManager.h"
#include "Entity.h"

class StartScreen : public Entity
{
private:
	int m_frame = 0;
	unsigned int m_VAO, m_vertexbufferID, m_indexbufferID;

public:
	StartScreen(int, float, float, float, EntityManager*);
	~StartScreen();

	void generateBuffers() override;

	void animateScreen() override;
};