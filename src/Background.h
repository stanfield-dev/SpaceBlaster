#pragma once

#include "Entity.h"

class Background : public Entity
{
private:

public:
	Background(int, float, float, float);
	~Background();

	void scrollBackground();
};
