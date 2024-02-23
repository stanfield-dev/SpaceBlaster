#include "Score.h"

Score::Score(int type, float x, float y, float z, EntityManager* entityManager)
	: Entity(type, x, y, z)
{
	generateBuffers();

	m_displayWidth = SCOREWIDTH;
	m_displayHeight = SCOREHEIGHT;
	m_positionXOffset = m_displayWidth / SCREENWIDTH;
	m_positionYOffset = m_displayHeight / SCREENHEIGHT;

	m_positionX1 = m_positionX + m_positionXOffset;
	m_positionX2 = m_positionX + (2 * m_positionXOffset);

	m_spriteSheetWidth = 960.0f;
	m_spriteSheetHeight = 96.0f;
	m_spriteWidth = 96.0f;
	m_spriteHeight = 96.0f;
	m_spriteXOffset = m_spriteWidth / m_spriteSheetWidth;
	m_spriteYOffset = m_spriteHeight / m_spriteSheetHeight;

	updateVertexArray();

	entityManager->addEntityToRegistry(this); // TODO: do i need to be an entity?
}

Score::~Score()
{
}

void Score::updateScore()
 {
	m_score++;

	std::string stringScore = std::to_string(m_score);

	if (m_score < 10) {
		m_scoreStruct.digit1s	= m_score * m_spriteXOffset;
	}
	else if ((m_score > 9) && (m_score < 100)) {
		m_scoreStruct.digit10s	= ((float)stringScore[0] - 48.0f) * m_spriteXOffset;
		m_scoreStruct.digit1s	= ((float)stringScore[1] - 48.0f) * m_spriteXOffset;
	}
	else if ((m_score > 99) && (m_score < 1000)) {
		m_scoreStruct.digit100s = ((float)stringScore[0] - 48.0f) * m_spriteXOffset;
		m_scoreStruct.digit10s	= ((float)stringScore[1] - 48.0f) * m_spriteXOffset;
		m_scoreStruct.digit1s	= ((float)stringScore[2] - 48.0f) * m_spriteXOffset;
	}
	// if the player beats score 999 their reward is crashing the game...

	// 100's
	m_vertexScoreArray[3]  = m_scoreStruct.digit100s;						// LLx
	m_vertexScoreArray[9]  = m_scoreStruct.digit100s + m_spriteXOffset;		// LRx
	m_vertexScoreArray[15] = m_scoreStruct.digit100s + m_spriteXOffset;		// URx
	m_vertexScoreArray[21] = m_scoreStruct.digit100s;						// ULx

	// 10's
	m_vertexScoreArray[27] = m_scoreStruct.digit10s;
	m_vertexScoreArray[33] = m_scoreStruct.digit10s + m_spriteXOffset;
	m_vertexScoreArray[39] = m_scoreStruct.digit10s + m_spriteXOffset;
	m_vertexScoreArray[45] = m_scoreStruct.digit10s;

	// 1's													 
	m_vertexScoreArray[51] = m_scoreStruct.digit1s;
	m_vertexScoreArray[57] = m_scoreStruct.digit1s + m_spriteXOffset;
	m_vertexScoreArray[63] = m_scoreStruct.digit1s + m_spriteXOffset;
	m_vertexScoreArray[69] = m_scoreStruct.digit1s;

	updateVertexArray();
}

void Score::generateBuffers()
{
	glGenVertexArrays(1, &m_VAO);
	glGenBuffers(1, &m_vertexbufferID);
	glGenBuffers(1, &m_indexbufferID);
}

float* Score::updateVertexArray()
{
	m_vertexScoreArray[0] = m_positionX;						// quad LL
	m_vertexScoreArray[1] = m_positionY;
	m_vertexScoreArray[2] = m_positionZ;
	m_vertexScoreArray[3] = m_scoreStruct.digit100s;							// texture LL
	m_vertexScoreArray[4] = m_spriteY;

	m_vertexScoreArray[6] = m_positionX + m_positionXOffset;	// LR
	m_vertexScoreArray[7] = m_positionY;
	m_vertexScoreArray[8] = m_positionZ;
	m_vertexScoreArray[9] = m_scoreStruct.digit100s + m_spriteXOffset;
	m_vertexScoreArray[10] = m_spriteY;

	m_vertexScoreArray[12] = m_positionX + m_positionXOffset;	// UR
	m_vertexScoreArray[13] = m_positionY + m_positionYOffset;
	m_vertexScoreArray[14] = m_positionZ;
	m_vertexScoreArray[15] = m_scoreStruct.digit100s + m_spriteXOffset;
	m_vertexScoreArray[16] = m_spriteY + m_spriteYOffset;

	m_vertexScoreArray[18] = m_positionX;						// UL
	m_vertexScoreArray[19] = m_positionY + m_positionYOffset;
	m_vertexScoreArray[20] = m_positionZ;
	m_vertexScoreArray[21] = m_scoreStruct.digit100s;
	m_vertexScoreArray[22] = m_spriteY + m_spriteYOffset;

	m_vertexScoreArray[24] = m_positionX1;						// quad LL
	m_vertexScoreArray[25] = m_positionY;
	m_vertexScoreArray[26] = m_positionZ;
	m_vertexScoreArray[27] = m_scoreStruct.digit10s;							// texture LL
	m_vertexScoreArray[28] = m_spriteY;

	m_vertexScoreArray[30] = m_positionX1 + m_positionXOffset;	// LR
	m_vertexScoreArray[31] = m_positionY;
	m_vertexScoreArray[32] = m_positionZ;
	m_vertexScoreArray[33] = m_scoreStruct.digit10s + m_spriteXOffset;
	m_vertexScoreArray[34] = m_spriteY;

	m_vertexScoreArray[36] = m_positionX1 + m_positionXOffset;	// UR
	m_vertexScoreArray[37] = m_positionY + m_positionYOffset;
	m_vertexScoreArray[38] = m_positionZ;
	m_vertexScoreArray[39] = m_scoreStruct.digit10s + m_spriteXOffset;
	m_vertexScoreArray[40] = m_spriteY + m_spriteYOffset;

	m_vertexScoreArray[42] = m_positionX1;						// UL
	m_vertexScoreArray[43] = m_positionY + m_positionYOffset;
	m_vertexScoreArray[44] = m_positionZ;
	m_vertexScoreArray[45] = m_scoreStruct.digit10s;
	m_vertexScoreArray[46] = m_spriteY + m_spriteYOffset;

	m_vertexScoreArray[48] = m_positionX2;						// quad LL
	m_vertexScoreArray[49] = m_positionY;
	m_vertexScoreArray[50] = m_positionZ;
	m_vertexScoreArray[51] = m_scoreStruct.digit1s;							// texture LL
	m_vertexScoreArray[52] = m_spriteY;

	m_vertexScoreArray[54] = m_positionX2 + m_positionXOffset;	// LR
	m_vertexScoreArray[55] = m_positionY;
	m_vertexScoreArray[56] = m_positionZ;
	m_vertexScoreArray[57] = m_scoreStruct.digit1s + m_spriteXOffset;
	m_vertexScoreArray[58] = m_spriteY;

	m_vertexScoreArray[60] = m_positionX2 + m_positionXOffset;	// UR
	m_vertexScoreArray[61] = m_positionY + m_positionYOffset;
	m_vertexScoreArray[62] = m_positionZ;
	m_vertexScoreArray[63] = m_scoreStruct.digit1s + m_spriteXOffset;
	m_vertexScoreArray[64] = m_spriteY + m_spriteYOffset;

	m_vertexScoreArray[66] = m_positionX2;						// UL
	m_vertexScoreArray[67] = m_positionY + m_positionYOffset;
	m_vertexScoreArray[68] = m_positionZ;
	m_vertexScoreArray[69] = m_scoreStruct.digit1s;
	m_vertexScoreArray[70] = m_spriteY + m_spriteYOffset;

	return m_vertexScoreArray;
}

void Score::updateVertexBuffer()
{
	int numberOfVertices = 72;
	int sizeOfBuffer = numberOfVertices * sizeof(float);

	glBindBuffer(GL_ARRAY_BUFFER, m_vertexbufferID);
	glBufferData(GL_ARRAY_BUFFER, sizeOfBuffer, (const void*)m_vertexScoreArray, GL_STATIC_DRAW);
	glEnableVertexAttribArray(0);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), 0);
	glEnableVertexAttribArray(1);
	glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (const void*)(3 * sizeof(float)));
	glEnableVertexAttribArray(2);
	glVertexAttribPointer(2, 1, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (const void*)(5 * sizeof(float)));
}

void Score::bindIBO()
{
	int numberOfIBOIndices = 18;

	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_indexbufferID);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, numberOfIBOIndices * sizeof(unsigned int), m_iboIndices, GL_STATIC_DRAW);
}

