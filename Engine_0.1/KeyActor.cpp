#include "KeyActor.h"

#include "GameSpace.h"
#include "Actor.h"
#include "Entitie.h"

KeyActor::KeyActor(GameSpace* space, Vector3 initPosition) : Key(space, initPosition, Block::WOOD)
{
	this->space_c = (GameSpace*)space;
}

void KeyActor::update()
{
	if (!Entitie::Distance(this->space_c->getActor()->getCamera()->getPosition(), body->getTransform().getPosition(), 3)) return;

	Key::update();
	if (space_c->getWorld()->testOverlap(body, space_c->getActor()->getBody())) {
		deleteData();
		space_c->deleteEntitie(this);
		cout << "Tienes una manzana" << endl;
		space_c->getActor()->addManzana();
	};
	
}
