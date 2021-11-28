#pragma once

#include "Key.h"

class KeyEnemy : public Key
{
public:

	KeyEnemy(GameSpace* space, Vector3 initPosition);
	void update();

public:

	GameSpace* space_c;
};

