#pragma once
#include "Space.h"

#include "Menu.h"
#include "MenuItem.h"
#include "GameSpace.h"

class Camera;
class Menu;
class MenuItem;

class MenuSpace : public Space
{
public:

	MenuSpace(Engine* engine);
	~MenuSpace();

	void render();
	void update();

	void updateMainMenu();
	void updateLevelsMenu();
	void updatePauseMenu();
	void updateInstructionMenu();
	void updateLoadingMenu();
	void updateWinLoseMenu();

	void setWinLose(int m);

	Camera* getCamera();


private:

	Camera* menuCamera;

	Menu* main_menu;
	Menu* levels_menu;
	Menu* pause_menu;
	Menu* instruction_menu;
	Menu* loading_menu;
	Menu* win_lose_menu;

	Menu* current_menu;

	int current_item;
	Dificultad current_dificultad;

	int win_lose;

	vector<Menu> m_menus;
};

