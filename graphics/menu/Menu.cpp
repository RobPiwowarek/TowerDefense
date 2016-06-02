#include "Menu.h"
#include "../GameWindow.h"
#include  <iostream>
#include <cstdio>
#include <cstdarg>

using namespace graphics;

Menu::Menu(GameWindow* parent) : Content(parent) {

}

Menu::~Menu() { }

bool Menu::addMenuItem(graphics::Label * label){

	for (graphics::Label* l : this->menu){
		if (l == label) {
			std::cout << "Failed to add item to menu, it already exists" << std::endl;
			return false;
		}
	}

	menu.push_back(label);

	return true;
}

void Menu::display() {
	static sf::Sprite background(*this->parent->getMenuBackground());

	this->parent->draw(background);

	for (graphics::Label* label : this->menu){
		label->display(*this->parent, "");
	}
}

void Menu::manageEvent(sf::Event& e) {

}

graphics::Label* Menu::getLabel(sf::Vector2f loc) const {
	for (Label* l : this->menu) {
		if (loc.x >= l->getLocation().x && loc.y >= l->getLocation().y && loc.x <= l->getLocation().x + l->getSize().x && loc.y <= l->getLocation().y + l->getSize().y)
			return l;
	}

	return nullptr;
}