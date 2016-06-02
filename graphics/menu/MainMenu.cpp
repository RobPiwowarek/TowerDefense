#include "MainMenu.h"
#include "../../threading/AppModel.h"

using namespace graphics;
using namespace sf;

#include <thread>

MainMenu::MainMenu(GameWindow* parent) : Menu(parent) {
	startGameButton = new Label(Vector2f(MENU_LABEL_WIDTH, MENU_LABEL_HEIGHT),
		Vector2f(MENU_LABEL_X, MENU_LABEL_Y), parent->getLabelBackground(), "START GAME");
	quitButton = new Label(Vector2f(MENU_LABEL_WIDTH, MENU_LABEL_HEIGHT),
		Vector2f(MENU_LABEL_X, MENU_LABEL_Y + MENU_LABEL_Y_DIFF), parent->getLabelBackground(), "QUIT");

	startGameButton->setFontSize(MENU_LABEL_FONT_SIZE);
	quitButton->setFontSize(MENU_LABEL_FONT_SIZE);

	this->addMenuItem(startGameButton);
	this->addMenuItem(quitButton);
}

MainMenu::~MainMenu() {
	delete this->startGameButton;
	delete this->quitButton;
}

void MainMenu::manageEvent(Event& e) {
	if (e.type == Event::MouseButtonPressed) {
		Label* cur;
		if (cur = this->getLabel(Vector2f(Mouse::getPosition() - parent->getPosition()))) {
			if (cur == startGameButton)
				AppModel::getInstance().createGame();

			else if (cur == quitButton) {
				exit(0);
			}
		}
	}
}
