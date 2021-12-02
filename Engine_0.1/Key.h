#pragma once
#include "Entitie.h"
#include "Engine.h"

class Actor;
class GameSpace;

class Key : public Entitie
{
protected:

	GameSpace* space_c;

public:

	Key(GameSpace* space, Vector3 initPosition, Block textura);
	void update();
};

