#include "Menu.h"
#include  <iostream>
#include <cstdio>
#include <cstdarg>

Menu::Menu(){}

Menu::Menu(int n, ...){
	va_list args;
	va_start(args, n);

	while (n-- > 0){
		this->menu.push_back(va_arg(args, graphics::Label*));
	}

	va_end(args);
}

Menu::Menu(std::vector<graphics::Label*> labels) {
	this->menu = labels;
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

void Menu::draw(sf::RenderWindow &window) {
	for (graphics::Label* label : this->menu){
		label->display(window, "");
	}
}

void Menu::moveUp() {
    if (selectedItemIndex >= 1) {
		this->menu[selectedItemIndex]->setForeColor(this->menu[selectedItemIndex]->getOriginalColor());
        selectedItemIndex--;
        menu[selectedItemIndex]->setForeColor(sf::Color::Red);
    }
}

void Menu::moveDown() {
    if (selectedItemIndex < MAX_NUMBER_OF_ITEMS - 1) {
        menu[selectedItemIndex]->setForeColor(this->menu[selectedItemIndex]->getOriginalColor());
        selectedItemIndex++;
        menu[selectedItemIndex]->setForeColor(sf::Color::Red);
    }
}
