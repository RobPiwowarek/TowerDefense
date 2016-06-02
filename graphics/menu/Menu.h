#ifndef MENU_H
#define MENU_H

#include "SFML/Graphics.hpp"
#include "../graphics/Label.h"
#include <set>

#define MAX_NUMBER_OF_ITEMS 3

namespace graphics {
    class Menu;
	class GameWindow;
}
namespace graphics {
	class Menu : public Content {
	public:
		/*Menu(int n, ...); // assuming: graphics::Label* 
		Menu(std::vector<graphics::Label*> labels);
		Menu();*/
		Menu(GameWindow* parent);

		~Menu();

		bool addMenuItem(graphics::Label* label);

		void display();

		void manageEvent(sf::Event& e);

		std::set<graphics::Label *>& getMenuItems() const;

		graphics::Label* getLabel(sf::Vector2f loc) const;
	private:
		int selectedItemIndex = 0;
		std::vector<graphics::Label*> menu;
	};
}

#endif
