#pragma once

#include <vector>

#include "Entitie.h"

class GameSpace;

class Cube: public Entitie
{
public:

	Cube(GameSpace* space, int texture, Vector3 initPosition);

};

