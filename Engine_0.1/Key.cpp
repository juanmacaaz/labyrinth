#include "Key.h"

#include "Engine.h"
#include "Actor.h"
#include "GameSpace.h"

Key::Key(GameSpace* space, Vector3 initPosition) :
	Entitie(space, "key", Block::WOOD, "basic-nolight", initPosition, 10)
{
	this->space = space;
	body->setType(BodyType::STATIC);
}

void Key::update()
{
	rotateY(0.01f);
	if (space->getWorld()->testOverlap(body, space->getActor()->getBody())) {
		deleteData();
		space->deleteEntitie(this);
		cout << "Tienes una manzana" << endl;
	};
}
