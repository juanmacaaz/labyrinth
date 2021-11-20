#include "MenuSpace.h"
#include "Engine.h"

MenuSpace::MenuSpace(Engine* engine) : Space(engine)
{
	PhysicsWorld::WorldSettings settings;
	settings.gravity = Vector3(0, -9.8f, 0);

	world = pc.createPhysicsWorld(settings);



	ProjectionData proyectionData = { 45.0f, 0.01f, 100.0f, this->engine->getWWidth() , this->engine->getWHeight() };

	menuCamera = new Camera(vec3(0.0f, 0.0f, 0.0f), vec3(1.0f, 0.0f, 0.0f), proyectionData, this->engine->getWWidth(), this->engine->getWHeight());


	main_menu = new Menu();
	levels_menu = new Menu();
	pause_menu = new Menu();
	instruction_menu = new Menu();

	
	//Main Menu
	main_menu->m_items.push_back(new MenuItem(this, "start", Block::WHITE, Vector3(20, -4, -8)));
	main_menu->m_items.push_back(new MenuItem(this, "levels", Block::WHITE, Vector3(20, -4, 0)));
	main_menu->m_items.push_back(new MenuItem(this, "exit", Block::WHITE, Vector3(20, -4, 8)));

	main_menu->m_items.push_back(new MenuItem(this, "title", Block::WALL, Vector3(6, 1, 0)));

	
	//Levels Menu
	levels_menu->m_items.push_back(new MenuItem(this, "castle", Block::WALL, Vector3(20, 0, -8)));
	levels_menu->m_items.push_back(new MenuItem(this, "jungle", Block::WALL, Vector3(20, 0, 0)));
	levels_menu->m_items.push_back(new MenuItem(this, "desert", Block::WALL, Vector3(20, 0, 8)));

	levels_menu->m_items.push_back(new MenuItem(this, "back", Block::WHITE, Vector3(20, -4, 0)));

	levels_menu->m_items.push_back(new MenuItem(this, "tower", Block::WALL, Vector3(20, 2, -8)));
	levels_menu->m_items.push_back(new MenuItem(this, "palm", Block::WALL, Vector3(20, 2, 0)));
	levels_menu->m_items.push_back(new MenuItem(this, "pyramid", Block::WALL, Vector3(20, 2, 8)));

	
	//Pause Menu
	pause_menu->m_items.push_back(new MenuItem(this, "start", Block::WHITE, Vector3(20, 3, 0)));
	pause_menu->m_items.push_back(new MenuItem(this, "exit", Block::WHITE, Vector3(20, -3, 0)));


	//Instruction Menu
	instruction_menu->m_items.push_back(new MenuItem(this, "start", Block::WHITE, Vector3(20, -4, 0)));


	current_menu = main_menu;
	current_item = 0;
	press = false;
}

void MenuSpace::render()
{
	current_menu->render_menu();
}

void MenuSpace::update()
{
	if(current_menu == main_menu) {
		updateMainMenu();
	}

	if (current_menu == levels_menu) {
		updateLevelsMenu();
	}

	if (current_menu == pause_menu) {
		updatePauseMenu();
	}

	if (current_menu == instruction_menu) {
		updateInstructionMenu();
	}

	isPressed();
}

Camera* MenuSpace::getCamera() {
	return menuCamera;
}

void MenuSpace::updateMainMenu() 
{
	if (!press) {
		switch (current_item) {
			case 0:	main_menu->m_items[0]->move_item(Vector3(16, -4, -8));
				if (glfwGetKey(this->getWindow(), GLFW_KEY_RIGHT) == GLFW_PRESS) {
					press = true;
					main_menu->m_items[0]->move_item(Vector3(20, -4, -8));
					current_item = 1;
				}
				if (glfwGetKey(this->getWindow(), GLFW_KEY_ENTER) == GLFW_PRESS) {
					press = true;
					current_menu = instruction_menu;
				}
				break;

			case 1: main_menu->m_items[1]->move_item(Vector3(16, -4, 0));
				if (glfwGetKey(this->getWindow(), GLFW_KEY_RIGHT) == GLFW_PRESS) {
					main_menu->m_items[1]->move_item(Vector3(20, -4, 0));
					press = true;
					current_item = 2;
				}
				if (glfwGetKey(this->getWindow(), GLFW_KEY_LEFT) == GLFW_PRESS) {
					main_menu->m_items[1]->move_item(Vector3(20, -4, 0));
					press = true;
					current_item = 0;
				}
				if (glfwGetKey(this->getWindow(), GLFW_KEY_ENTER) == GLFW_PRESS) {
					main_menu->m_items[1]->move_item(Vector3(20, -4, 0));
					press = true;
					current_item = 0;
					current_menu = levels_menu;
				}
				break;

			case 2: main_menu->m_items[2]->move_item(Vector3(16, -4, 8));
				if (glfwGetKey(this->getWindow(), GLFW_KEY_LEFT) == GLFW_PRESS) {
					press = true;
					main_menu->m_items[2]->move_item(Vector3(20, -4, 8));
					current_item = 1;
				}
				if (glfwGetKey(this->getWindow(), GLFW_KEY_ENTER) == GLFW_PRESS) {
					glfwSetWindowShouldClose(this->getWindow(), GL_TRUE);
				}
				break;
		}
	}	
}

void MenuSpace::updateLevelsMenu() {
	if (!press) {
		switch (current_item) {
		case 0:	levels_menu->m_items[0]->move_item(Vector3(16, 0, -8));
			if (glfwGetKey(this->getWindow(), GLFW_KEY_RIGHT) == GLFW_PRESS) {
				levels_menu->m_items[0]->move_item(Vector3(20, 0, -8));
				press = true;
				current_item = 1;
			}
			break;

		case 1: levels_menu->m_items[1]->move_item(Vector3(16, 0, 0));
			if (glfwGetKey(this->getWindow(), GLFW_KEY_RIGHT) == GLFW_PRESS) {
				press = true;
				levels_menu->m_items[1]->move_item(Vector3(20, 0, 0));
				current_item = 2;
			}
			if (glfwGetKey(this->getWindow(), GLFW_KEY_LEFT) == GLFW_PRESS) {
				press = true;
				levels_menu->m_items[1]->move_item(Vector3(20, 0, 0));
				current_item = 0;
			}
			if (glfwGetKey(this->getWindow(), GLFW_KEY_DOWN) == GLFW_PRESS) {
				press = true;
				levels_menu->m_items[1]->move_item(Vector3(20, 0, 0));
				current_item = 3;
			}
			break;

		case 2: levels_menu->m_items[2]->move_item(Vector3(16, 0, 8));
			if (glfwGetKey(this->getWindow(), GLFW_KEY_LEFT) == GLFW_PRESS) {
				press = true;
				levels_menu->m_items[2]->move_item(Vector3(20, 0, 8));
				current_item = 1;
			}
			break;

		case 3: levels_menu->m_items[3]->move_item(Vector3(16, -4, 0));
			if (glfwGetKey(this->getWindow(), GLFW_KEY_UP) == GLFW_PRESS) {
				press = true;
				levels_menu->m_items[3]->move_item(Vector3(20, -4, 0));
				current_item = 1;
			}
			if (glfwGetKey(this->getWindow(), GLFW_KEY_ENTER) == GLFW_PRESS) {
				levels_menu->m_items[3]->move_item(Vector3(20, -4, 0));
				press = true;
				current_item = 0;
				current_menu = main_menu;
			}
			break;
		}
	}	
}

void MenuSpace::updatePauseMenu()
{
	if (!press) {
		switch (current_item) {
		case 0:	pause_menu->m_items[0]->move_item(Vector3(16, 3, 0));
			if (glfwGetKey(this->getWindow(), GLFW_KEY_DOWN) == GLFW_PRESS) {
				pause_menu->m_items[0]->move_item(Vector3(20, 3, 0));
				press = true;
				current_item = 1;
			}
			if (glfwGetKey(this->getWindow(), GLFW_KEY_ENTER) == GLFW_PRESS) {
				press = true;
				engine->setGameSpace();
			}
			break;

		case 1: pause_menu->m_items[1]->move_item(Vector3(16, -3, 0));
			if (glfwGetKey(this->getWindow(), GLFW_KEY_UP) == GLFW_PRESS) {
				press = true;
				pause_menu->m_items[1]->move_item(Vector3(20, -3, 0));
				current_item = 0;
			}
			if (glfwGetKey(this->getWindow(), GLFW_KEY_ENTER) == GLFW_PRESS) {
				pause_menu->m_items[1]->move_item(Vector3(20, -3, 0));
				press = true;
				current_item = 0;
				current_menu = main_menu;
			}
			break;
		}
	}
}

void MenuSpace::updateInstructionMenu() 
{
	if (!press) {
		switch (current_item) {
		case 0:	instruction_menu->m_items[0]->move_item(Vector3(16, -4, 0));
			if (glfwGetKey(this->getWindow(), GLFW_KEY_ENTER) == GLFW_PRESS) {
				instruction_menu->m_items[0]->move_item(Vector3(20, -4, 0));
				press = true;
				current_menu = pause_menu;
				engine->setGameSpace();
			}
			break;
		}
	}
}