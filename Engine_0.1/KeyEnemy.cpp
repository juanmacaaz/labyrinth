#include "KeyEnemy.h"

#include "GameSpace.h"
#include "Actor.h"
#include "Enemy.h"
#include "HudSpace.h"

KeyEnemy::KeyEnemy(GameSpace* space, Vector3 initPosition): Key(space, initPosition, Block::EKEY)
{
	n_keys = 0;
	this->space_c = (GameSpace*) space;
	body->getCollider(0)->setCollisionCategoryBits(0x0002);
	body->getCollider(0)->setCollideWithMaskBits(0x0002);
}

void KeyEnemy::update()
{
	Key::update();
	if (space_c->getWorld()->testOverlap(body, space_c->getEnemy()->getBody())) {
		space->getEngine()->hudSpace->updateEnemyScore(space_c->getEnemy()->n_llave++);
		deleteData();
		space_c->deleteEntitie(this);
		cout << "El enemigo tiene una manzana" << endl;
	};
}
