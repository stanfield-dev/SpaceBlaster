#pragma once

// friendly names for entities
enum objectType : int
{
	BACKGROUND = 0,
	PLAYER,
	ENEMY,
	PROJECTILE,
	EXPLOSION,
	STARTSCREEN,
	HELPSCREEN,
	COUNTDOWN,
	SCORE,
	HEALTHBAR,
	GAMEOVER
};

// game states referenced by Game and Renderer
enum m_gameState : int
{
	COMBATst,
	COUNTDOWNst,
	GAMEOVERst,
	HELPSCREENst,
	NEWGAMEst,
	RESPAWNst,
	STARTSCREENst
};

// for collision checking
typedef struct
{
	float left;
	float right;
	float top;
	float bottom;
} m_boundingBox;
