#pragma once
#include "Entitie.h"

class GameSpace;

class Enemy :
    public Entitie
{
private:

	GameSpace* space;
	float velocity;
	int visita_pos;
	long timer;

public:

	Enemy(GameSpace* space, Vector3 initPosition);
	bool moveTo(float x, float y);
	void update();
	void nextPosition();
	int getPosition();
};

