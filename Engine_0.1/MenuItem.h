#pragma once

#include <vector>
#include <string>

#include "Menu.h"
#include "Entitie.h"
#include "MenuSpace.h"

using namespace std;

class MenuSpace;


enum Button
{
	START = 1,
	LEVELS = 2,
	EXIT = 3,
};

class MenuItem : public Entitie
{
public:

	MenuItem(MenuSpace* space, string name, int texture, Vector3 initPosition, float scale = 1.0f);

	void render_item();
	void remove_item();

	void move_item(const Vector3& v);

	void update();

	Vector3 getPosition();

	MenuSpace* space;
private:

	Vector3 pos;

};
