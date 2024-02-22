#pragma once
#include "EntityManager.h"
#include "Entity.h"

class HelpMenu : public Entity
{
private:
	int m_frame = 0;
	unsigned int m_VAO, m_vertexbufferID, m_indexbufferID;

public:
	HelpMenu(int, float, float, float, EntityManager*);
	~HelpMenu();

	void generateBuffers() override;
	void animateMenu() override;
};