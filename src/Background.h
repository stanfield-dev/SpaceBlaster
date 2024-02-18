#pragma once

#include "EntityManager.h"
#include "Entity.h"

class Background : public Entity
{
private:

public:
	Background(int, float, float, float, EntityManager*);
	~Background();

	void scrollBackground() override;
};
