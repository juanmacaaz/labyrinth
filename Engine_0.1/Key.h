#pragma once
#include "Entitie.h"

class Actor;
class Space;

class Key : public Entitie
{
private:

	Space* space;

public:

	Key(Space* space, Vector3 initPosition);
	void update();
};

