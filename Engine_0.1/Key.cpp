#include "Key.h"

#include "Engine.h"
#include "Actor.h"

Key::Key(Space* space, Vector3 initPosition) :
	Entitie(space, "key", Block::WOOD, "basic-nolight", initPosition, 5)
{
	this->space = space;
	body->setType(BodyType::STATIC);
}

void Key::update()
{
	if (space->getWorld()->testOverlap(body, space->getActor()->getBody())) {
		cout << "Han colisionado!!" << endl;
	};
}
