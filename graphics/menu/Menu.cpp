#include "Menu.h"
#include  <iostream>
Menu::Menu(float width, float height) {
	if (!font.loadFromFile("arial.ttf")) {
		std::cout << "Error loading font";
		return;
        // todo: handle error
    }

    // Set basic menu items

    menu[0].setFont(font);
    menu[0].setColor(sf::Color::Red);
    menu[0].setString("Play");
    menu[0].setPosition(sf::Vector2f(width/2, height/(MAX_NUMBER_OF_ITEMS+1)*1));

    menu[1].setFont(font);
    menu[1].setColor(sf::Color::White);
    menu[1].setString("Options");
    menu[1].setPosition(sf::Vector2f(width/2, height/(MAX_NUMBER_OF_ITEMS+1)*2));

    menu[2].setFont(font);
	menu[2].setColor(sf::Color::White);
    menu[2].setString("Exit");
    menu[2].setPosition(sf::Vector2f(width/2, height/(MAX_NUMBER_OF_ITEMS+1)*3));

    selectedItemIndex = 0;
}


Menu::~Menu() { }

int Menu::getPressedItem() { return selectedItemIndex; }

void Menu::draw(sf::RenderWindow &window) {
    for (int i = 0; i < MAX_NUMBER_OF_ITEMS; i++){
        window.draw(menu[i]);
    }
}

void Menu::moveUp() {
    if (selectedItemIndex >= 1){
        menu[selectedItemIndex].setColor(sf::Color::White);
        selectedItemIndex--;
        menu[selectedItemIndex].setColor(sf::Color::Red);
    }
}

void Menu::moveDown() {
    if (selectedItemIndex < MAX_NUMBER_OF_ITEMS-1){
        menu[selectedItemIndex].setColor(sf::Color::White);
        selectedItemIndex++;
        menu[selectedItemIndex].setColor(sf::Color::Red);
    }
}