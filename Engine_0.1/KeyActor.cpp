#include "KeyActor.h"

#include "GameSpace.h"
#include "Actor.h"

KeyActor::KeyActor(GameSpace* space, Vector3 initPosition) : Key(space, initPosition, Block::WOOD)
{
	this->space_c = (GameSpace*)space;
}

void KeyActor::update()
{
	Key::update();
	if (space_c->getWorld()->testOverlap(body, space_c->getActor()->getBody())) {
		deleteData();
		space_c->deleteEntitie(this);
		cout << "Tienes una manzana" << endl;
		space_c->getActor()->addManzana();
	};
	
}
