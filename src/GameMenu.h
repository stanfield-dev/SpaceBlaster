#pragma once
#include "EntityManager.h"
#include "Entity.h"

class GameMenu : public Entity
{
private:
	int m_frame = 0;
	unsigned int m_VAO, m_vertexbufferID, m_indexbufferID;

public:
	GameMenu(int, float, float, float, EntityManager*);
	~GameMenu();

	void generateBuffers() override;
	void animateMenu() override;
};