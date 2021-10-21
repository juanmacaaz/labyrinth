#pragma once

#include <vector>


using namespace std;

#include "MenuItem.h"

class MenuItem;

class Menu
{
public:

	Menu();

	void render_menu();
	void remove_menu();
	
	vector<MenuItem*> m_items;

private:

};



