#include "Projectile.h"
#include "EntityManager.h"

Projectile::Projectile(int type, float x, float y, float z)
	: Entity(type, x, y, z)
{
	EntityManager::addEntityToRegistry(this);
}

Projectile::~Projectile()
{
}


