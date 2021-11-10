#pragma once
#include "Entitie.h"

class GameSpace;

class Enemy :
    public Entitie
{
private:

	GameSpace* space;
	float velocity;

public:

	Enemy(GameSpace* space, Vector3 initPosition);
	void moveTo(float x, float y);
};

