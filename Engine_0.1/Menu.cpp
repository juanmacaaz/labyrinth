#include "Menu.h"


Menu::Menu() {
}

void Menu::render_menu() {
	for (auto i : m_items) {
		i->render_item();
	}
}

void Menu::remove_menu() {
	for (auto i : m_items) {
		i->remove_item();
	}
}