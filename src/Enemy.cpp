#include <GL/glew.h>
#include <GLFW/glfw3.h>

#include "Enemy.h"
#include "EntityManager.h"

Enemy::Enemy(int type, float x, float y, float z)
	: Entity(type, x, y, z)
{
	EntityManager::addEntityToRegistry(this);
}

Enemy::~Enemy()
{
}


