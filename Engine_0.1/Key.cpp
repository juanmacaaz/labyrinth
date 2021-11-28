#include "Key.h"


#include "Actor.h"
#include "GameSpace.h"

Key::Key(GameSpace* space, Vector3 initPosition, Block textura) :
	Entitie(space, "key", textura, "basic-nolight", initPosition, 3)
{
	this->space = space;
	body->setType(BodyType::STATIC);
}

void Key::update()
{
	rotateY(0.01f);
}
