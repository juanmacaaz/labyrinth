#include "Cube.h"

Cube::Cube(Space* space, int texture, Vector3 initPosition) : 
	Entitie(space, "cube", texture, "basic-nolight", initPosition)
{
	body->setType(BodyType::STATIC);
}
