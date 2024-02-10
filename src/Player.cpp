#include <GL/glew.h>
#include <GLFW/glfw3.h>

#include "Player.h"
#include "EntityManager.h"

Player::Player(int type, float x, float y, float z)
	: Entity(type, x, y, z)
{
	EntityManager::addEntityToRegistry(this);
}

Player::~Player()
{
}






