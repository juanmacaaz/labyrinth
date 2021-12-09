#pragma once

#include "Key.h"

class KeyEnemy : public Key
{
public:

	KeyEnemy(GameSpace* space, Vector3 initPosition);
	void update();

public:

	int n_keys;
	GameSpace* space_c;
};

