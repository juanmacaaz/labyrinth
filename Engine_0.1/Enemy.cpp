#include "Enemy.h"

#include <gtc/quaternion.hpp>

#include "GameSpace.h"
#include "Space.h"
#include "Engine.h"
#include "Actor.h"

Enemy::Enemy(GameSpace* space, Vector3 initPosition):
	Entitie(space, "waifu", Block::WOOD, "basic-nolight", initPosition, 0.60f)
{
	timer = 0;
	this->visita_pos = 0;
	this->space = space;
	body->getCollider(0)->getMaterial().setFrictionCoefficient(0.005);
	body->getCollider(0)->getMaterial().setBounciness(0);
	body->enableGravity(false);
	body->setType(BodyType::STATIC);
	velocity = 0.01f;
}

bool Enemy::moveTo(float x, float z)
{
	Vector3 actPos = body->getTransform().getPosition();

	float x_m = x - actPos.x;  
	float z_m = z - actPos.z;

	if (abs(x_m) + abs(z_m) < 0.002f) {
		visita_pos++;
		return true;
	}
	
	int x_o = 0;
	int z_o = 0;

	if (abs(x_m) > 0.001) x_o = (x_m >= 0) ? 2 : -2;
	if (abs(z_m) > 0.001) z_o = (z_m >= 0) ? 2 : -2;

	qua<float> a = safeQuatLookAt(vec3(x, 1, z), vec3(actPos.x, 1, actPos.z), vec3(0, 1, 0), vec3(0, 1, 0));
	body->setTransform(Transform(Vector3((velocity * x_o) + actPos.x, actPos.y, (velocity * z_o) + actPos.z),  Quaternion(a.x, a.y, a.z, a.w)));
	return false;
}

void Enemy::update()
{
	if (space->getWorld()->testOverlap(body, space->getActor()->getBody())) {
		space->getActor()->toInitPosition();
	};
}

void Enemy::nextPosition()
{
	visita_pos++;
}

int Enemy::getPosition() {
	return visita_pos;
}