#include "Cube.h"

#include "GameSpace.h"
#include "Space.h"

Cube::Cube(GameSpace* space, int texture, Vector3 initPosition) : 
	Entitie(space, "cube", texture, "basic-nolight", initPosition)
{
	body->setType(BodyType::STATIC);
}
