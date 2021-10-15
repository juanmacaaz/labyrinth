#pragma once
#include "Entitie.h"

class Actor;
class GameSpace;

class Key : public Entitie
{
private:

	GameSpace* space;

public:

	Key(GameSpace* space, Vector3 initPosition);
	void update();
};

