#include "Key.h"

#include "Actor.h"
#include "GameSpace.h"

Key::Key(GameSpace* space, Vector3 initPosition, Block textura) :
	Entitie(space, "key", textura, "basic-nolight", initPosition, 3)
{
	this->space_c = space;
	body->setType(BodyType::STATIC);
}

void Key::update()
{
	if (!Entitie::Distance(this->space_c->getActor()->getCamera()->getPosition(), body->getTransform().getPosition(), 3)) return;
	rotateY(0.01f);
}
