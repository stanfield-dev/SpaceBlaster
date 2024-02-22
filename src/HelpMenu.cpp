#include "HelpMenu.h"
#include "EntityManager.h"

HelpMenu::HelpMenu(int type, float x, float y, float z, EntityManager* entityManager)
	: Entity(type, x, y, z)
{
	generateBuffers();

	m_displayWidth = SCREENWIDTH;
	m_displayHeight = SCREENHEIGHT;
	m_positionXOffset = (m_displayWidth / SCREENWIDTH) * 2;
	m_positionYOffset = (m_displayHeight / SCREENHEIGHT) * 2;

	m_spriteSheetWidth = 3200.0f;
	m_spriteSheetHeight = 1200.0f;
	m_spriteWidth = 1600.0f;
	m_spriteHeight = 1200.0f;
	m_spriteXOffset = m_spriteWidth / m_spriteSheetWidth;
	m_spriteYOffset = m_spriteHeight / m_spriteSheetHeight;

	updateVertexArray();

	entityManager->addEntityToRegistry(this);
}

HelpMenu::~HelpMenu()
{
}

void HelpMenu::generateBuffers()
{
	glGenVertexArrays(1, &m_VAO);
	glGenBuffers(1, &m_vertexbufferID);
	glGenBuffers(1, &m_indexbufferID);
}

void HelpMenu::animateMenu()
{
	if (m_frame > 20) {
		if (m_spriteX + m_spriteXOffset >= 1.0f) {
			m_spriteX = 0.0f;
		}
		else {
			m_spriteX += m_spriteXOffset;
		}

		m_vertexArray[3] = m_spriteX;						// LLx
		m_vertexArray[9] = m_spriteX + m_spriteXOffset;		// LRx
		m_vertexArray[15] = m_spriteX + m_spriteXOffset;	// URx
		m_vertexArray[21] = m_spriteX;						// ULx

		updateVertexArray();
		m_frame = 0;
	}

	m_frame++;
}