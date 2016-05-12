#ifndef MENU_H
#define MENU_H

#include "SFML/Graphics.hpp"
#include "../graphics/Label.h"
#include <set>

#define MAX_NUMBER_OF_ITEMS 3

namespace graphics {
    class Menu;
}

class Menu {
public:
	Menu(int n, ...); // assuming: graphics::Label* 
    Menu(std::vector<graphics::Label*> labels);
	Menu();

    ~Menu();

	bool addMenuItem(graphics::Label* label);

    void draw(sf::RenderWindow &window);

    void moveUp();

    void moveDown();

	std::set<graphics::Label *>& getMenuItems() const;

	graphics::Label* getCurrentItem() const;

private:
	int selectedItemIndex = 0;
	std::vector<graphics::Label*> menu;
};


#endif //TOWERDEFENSE_MENU_H
