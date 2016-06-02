#ifndef MAIN_MENU
#define MAIN_MENU

#include "Menu.h"

namespace graphics {

	class MainMenu : public Menu {
		const static int MENU_LABEL_WIDTH = 300;
		const static int MENU_LABEL_HEIGHT = 50;
		const static int MENU_LABEL_X = 270;
		const static int MENU_LABEL_Y = 100;
		const static int MENU_LABEL_Y_DIFF = 75;
		const static int MENU_LABEL_FONT_SIZE = 30;
	public:
		MainMenu(GameWindow* parent);
		~MainMenu();

		// manages event
		void manageEvent(sf::Event& e);
	private:

		Label* startGameButton;
		Label* quitButton;
	};
}

#endif