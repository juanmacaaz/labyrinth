#include "MenuItem.h"
#include "Engine.h"


MenuItem::MenuItem(MenuSpace* space, string name, int texture, Vector3 initPosition) : 
	Entitie(space, name, texture, "basic-nolight", initPosition)
{
	this->space = space;
	this->pos = initPosition;
	body->setType(BodyType::STATIC);
}

void MenuItem::render_item() 
{
	this->render(space->getCamera());
}

void MenuItem::remove_item() 
{
	deleteData();
	space->deleteEntitie(this);
}

void MenuItem::move_item(const Vector3 &v) {
	this->pos = v;
	body->setTransform(Transform(v, Quaternion::identity()));
}

Vector3 MenuItem::getPosition() {
	return pos;
}

void MenuItem::update() {
	rotateY(0.01f);
}
