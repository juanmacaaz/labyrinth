#pragma once

#include <vector>

#include "Entitie.h"

class Space;

class Cube: public Entitie
{
public:

	Cube(Space* space, int texture, Vector3 initPosition);

};

