#pragma once
#include "Space.h"

#include "Menu.h"
#include "MenuItem.h"

class Camera;
class Menu;
class MenuItem;

class MenuSpace : public Space
{
public:

	MenuSpace(Engine* engine);

	void render();
	void update();

	void updateMainMenu();
	void updateLevelsMenu();
	void updatePauseMenu();
	void updateInstructionMenu();

	Camera* getCamera();


private:

	Camera* menuCamera;

	Menu* main_menu;
	Menu* levels_menu;
	Menu* pause_menu;
	Menu* instruction_menu;

	Menu* current_menu;
	
	int current_item;

	vector<Menu> m_menus;
};

