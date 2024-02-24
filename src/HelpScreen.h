#pragma once
#include "EntityManager.h"
#include "Entity.h"

class HelpScreen : public Entity
{
private:
	int m_frame = 0;
	unsigned int m_VAO, m_vertexbufferID, m_indexbufferID;

public:
	HelpScreen(int, float, float, float, EntityManager*);
	~HelpScreen();

	void generateBuffers() override;
	void animateMenu() override;
};