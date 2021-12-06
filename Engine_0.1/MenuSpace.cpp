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
	main_menu->m_items.push_back(new MenuItem(this, "start_button", Block::FLOOR, Vector3(30, -6, -12)));
	main_menu->m_items.push_back(new MenuItem(this, "levels_button", Block::FLOOR, Vector3(30, -6, 0)));
	main_menu->m_items.push_back(new MenuItem(this, "exit_button", Block::FLOOR, Vector3(30, -6, 12)));

	main_menu->m_items.push_back(new MenuItem(this, "main_title", Block::FLOOR, Vector3(6, 0.1, 0)));

	
	//Levels Menu
	levels_menu->m_items.push_back(new MenuItem(this, "castle_button", Block::WALL, Vector3(32, 5, -10)));
	levels_menu->m_items.push_back(new MenuItem(this, "jungle_button", Block::WALL, Vector3(32, 0, -10)));
	levels_menu->m_items.push_back(new MenuItem(this, "desert_button", Block::WALL, Vector3(32, -5, -10)));

	levels_menu->m_items.push_back(new MenuItem(this, "back_button", Block::FLOOR, Vector3(28, -8, -14)));
	
	levels_menu->m_items.push_back(new MenuItem(this, "tower", Block::WALL, Vector3(12, -1, 20)));
	levels_menu->m_items.push_back(new MenuItem(this, "palm", Block::WALL, Vector3(12, -1, 20)));
	levels_menu->m_items.push_back(new MenuItem(this, "pyramid", Block::WALL, Vector3(12, -1, 20)));

	levels_menu->m_items.push_back(new MenuItem(this, "low_text", Block::WALL, Vector3(30, -8, 30)));
	levels_menu->m_items.push_back(new MenuItem(this, "medium_text", Block::WALL, Vector3(30, -8, 30)));
	levels_menu->m_items.push_back(new MenuItem(this, "high_text", Block::WALL, Vector3(30, -8, 30)));

	levels_menu->m_items.push_back(new MenuItem(this, "x", Block::WALL, Vector3(32, 5, -4)));

	levels_menu->m_items.push_back(new MenuItem(this, "levels_title", Block::WALL, Vector3(16, 4.5, -8)));
	levels_menu->m_items.push_back(new MenuItem(this, "difficulty_text", Block::WALL, Vector3(30, -8, 3)));

	
	//Pause Menu
	pause_menu->m_items.push_back(new MenuItem(this, "continue_button", Block::FLOOR, Vector3(30, 3, 0)));
	pause_menu->m_items.push_back(new MenuItem(this, "return_main_menu", Block::FLOOR, Vector3(30, -3, 0)));


	//Instruction Menu
	instruction_menu->m_items.push_back(new MenuItem(this, "start_button", Block::FLOOR, Vector3(30, -4, 0)));


	current_menu = main_menu;
	current_item = 0;
	this->current_dificultad = { 1, 8, 11, 0.2, 0.2 };
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
		levels_menu->m_items[4]->update();
		levels_menu->m_items[5]->update();
		levels_menu->m_items[6]->update();
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
			case 0:	main_menu->m_items[0]->move_item(Vector3(25, -6, -12));
				if (glfwGetKey(this->getWindow(), GLFW_KEY_RIGHT) == GLFW_PRESS) {
					press = true;
					main_menu->m_items[0]->move_item(Vector3(30, -6, -12));
					current_item = 1;
				}
				if (glfwGetKey(this->getWindow(), GLFW_KEY_ENTER) == GLFW_PRESS) {
					press = true;
					current_menu = instruction_menu;
				}
				break;

			case 1: main_menu->m_items[1]->move_item(Vector3(25, -6, 0));
				if (glfwGetKey(this->getWindow(), GLFW_KEY_RIGHT) == GLFW_PRESS) {
					main_menu->m_items[1]->move_item(Vector3(30, -6, 0));
					press = true;
					current_item = 2;
				}
				if (glfwGetKey(this->getWindow(), GLFW_KEY_LEFT) == GLFW_PRESS) {
					main_menu->m_items[1]->move_item(Vector3(30, -6, 0));
					press = true;
					current_item = 0;
				}
				if (glfwGetKey(this->getWindow(), GLFW_KEY_ENTER) == GLFW_PRESS) {
					main_menu->m_items[1]->move_item(Vector3(30, -6, 0));
					press = true;
					current_item = 0;
					current_menu = levels_menu;
				}
				break;

			case 2: main_menu->m_items[2]->move_item(Vector3(25, -6, 12));
				if (glfwGetKey(this->getWindow(), GLFW_KEY_LEFT) == GLFW_PRESS) {
					press = true;
					main_menu->m_items[2]->move_item(Vector3(30, -6, 12));
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
		case 0:	levels_menu->m_items[0]->move_item(Vector3(28, 5, -10));
			levels_menu->m_items[4]->move_item(Vector3(12, -1, 3));
			levels_menu->m_items[5]->move_item(Vector3(12, -1, 30));
			levels_menu->m_items[6]->move_item(Vector3(12, -1, 30));

			levels_menu->m_items[7]->move_item(Vector3(30, -8, 12));
			levels_menu->m_items[8]->move_item(Vector3(30, -8, 30));
			levels_menu->m_items[9]->move_item(Vector3(30, -8, 30));
			if (glfwGetKey(this->getWindow(), GLFW_KEY_DOWN) == GLFW_PRESS) {
				press = true;
				levels_menu->m_items[0]->move_item(Vector3(32, 5, -10));
				current_item = 1;
			}
			if (glfwGetKey(this->getWindow(), GLFW_KEY_ENTER) == GLFW_PRESS) {
				press = true;
				levels_menu->m_items[0]->move_item(Vector3(32, 5, -10));
				levels_menu->m_items[10]->move_item(Vector3(32, 5, -4));
				this->current_dificultad = { 1, 8, 11, 0.2, 0.2 };
			}
			break;

		case 1: levels_menu->m_items[1]->move_item(Vector3(28, 0, -10));
			levels_menu->m_items[4]->move_item(Vector3(12, -1, 30));
			levels_menu->m_items[5]->move_item(Vector3(12, -1, 3));
			levels_menu->m_items[6]->move_item(Vector3(12, -1, 30));

			levels_menu->m_items[7]->move_item(Vector3(30, -8, 30));
			levels_menu->m_items[8]->move_item(Vector3(30, -8, 14));
			levels_menu->m_items[9]->move_item(Vector3(30, -8, 30));
			if (glfwGetKey(this->getWindow(), GLFW_KEY_DOWN) == GLFW_PRESS) {
				press = true;
				levels_menu->m_items[1]->move_item(Vector3(32, 0, -10));
				current_item = 2;
			}
			if (glfwGetKey(this->getWindow(), GLFW_KEY_UP) == GLFW_PRESS) {
				press = true;
				levels_menu->m_items[1]->move_item(Vector3(32, 0, -10));
				current_item = 0;
			}
			if (glfwGetKey(this->getWindow(), GLFW_KEY_ENTER) == GLFW_PRESS) {
				press = true;
				levels_menu->m_items[1]->move_item(Vector3(32, 0, -10));
				levels_menu->m_items[10]->move_item(Vector3(32, 0, -4));
				this->current_dificultad = { 1, 15, 21, 0.2, 0.2 };
			}
			break;

		case 2: levels_menu->m_items[2]->move_item(Vector3(28, -5, -10));
			levels_menu->m_items[4]->move_item(Vector3(12, -1, 30));
			levels_menu->m_items[5]->move_item(Vector3(12, -1, 30));
			levels_menu->m_items[6]->move_item(Vector3(12, -1, 3));

			levels_menu->m_items[7]->move_item(Vector3(30, -8, 30));
			levels_menu->m_items[8]->move_item(Vector3(30, -8, 30));
			levels_menu->m_items[9]->move_item(Vector3(30, -8, 13));
			if (glfwGetKey(this->getWindow(), GLFW_KEY_DOWN) == GLFW_PRESS) {
				press = true;
				levels_menu->m_items[2]->move_item(Vector3(32, -5, -10));
				current_item = 3;
			}
			if (glfwGetKey(this->getWindow(), GLFW_KEY_UP) == GLFW_PRESS) {
				press = true;
				levels_menu->m_items[2]->move_item(Vector3(32, -5, -10));
				current_item = 1;
			}
			if (glfwGetKey(this->getWindow(), GLFW_KEY_ENTER) == GLFW_PRESS) {
				press = true;
				levels_menu->m_items[2]->move_item(Vector3(32, -5, -10));
				levels_menu->m_items[10]->move_item(Vector3(32, -5, -4));
				this->current_dificultad = { 2, 22, 31, 0.2, 0.2 };
			}
			break;

		case 3: levels_menu->m_items[3]->move_item(Vector3(25, -8, -14));
			if (glfwGetKey(this->getWindow(), GLFW_KEY_UP) == GLFW_PRESS) {
				press = true;
				levels_menu->m_items[3]->move_item(Vector3(28, -8, -14));
				current_item = 2;
			}
			if (glfwGetKey(this->getWindow(), GLFW_KEY_ENTER) == GLFW_PRESS) {
				levels_menu->m_items[3]->move_item(Vector3(28, -8, -14));
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
		case 0:	pause_menu->m_items[0]->move_item(Vector3(25, 3, 0));
			if (glfwGetKey(this->getWindow(), GLFW_KEY_DOWN) == GLFW_PRESS) {
				pause_menu->m_items[0]->move_item(Vector3(30, 3, 0));
				press = true;
				current_item = 1;
			}
			if (glfwGetKey(this->getWindow(), GLFW_KEY_ENTER) == GLFW_PRESS) {
				press = true;
				engine->setGameSpace();
			}
			break;

		case 1: pause_menu->m_items[1]->move_item(Vector3(25, -3, 0));
			if (glfwGetKey(this->getWindow(), GLFW_KEY_UP) == GLFW_PRESS) {
				press = true;
				pause_menu->m_items[1]->move_item(Vector3(30, -3, 0));
				current_item = 0;
			}
			if (glfwGetKey(this->getWindow(), GLFW_KEY_ENTER) == GLFW_PRESS) {
				pause_menu->m_items[1]->move_item(Vector3(30, -3, 0));
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
		case 0:	instruction_menu->m_items[0]->move_item(Vector3(25, -4, 0));
			if (glfwGetKey(this->getWindow(), GLFW_KEY_ENTER) == GLFW_PRESS) {
				instruction_menu->m_items[0]->move_item(Vector3(30, -4, 0));
				press = true;
				current_menu = pause_menu;
				engine->initGameSpace(this->current_dificultad);
				engine->setGameSpace();
			}
			break;
		}
	}
}