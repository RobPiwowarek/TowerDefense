#include "PauseMenu.h"
#include "../../threading/AppModel.h"

using namespace graphics;
using namespace sf;

PauseMenu::PauseMenu(GameWindow* g) : Menu(g) {
	continueButton = new Label(Vector2f(MENU_LABEL_WIDTH, MENU_LABEL_HEIGHT),
		Vector2f(MENU_LABEL_X, MENU_LABEL_Y), parent->getLabelBackground(), "CONTINUE");
	quitButton = new Label(Vector2f(MENU_LABEL_WIDTH, MENU_LABEL_HEIGHT),
		Vector2f(MENU_LABEL_X, MENU_LABEL_Y + 2 * MENU_LABEL_Y_DIFF), parent->getLabelBackground(), "QUIT GAME");
	quitToMainMenuButton = new Label(Vector2f(MENU_LABEL_WIDTH, MENU_LABEL_HEIGHT),
		Vector2f(MENU_LABEL_X, MENU_LABEL_Y + MENU_LABEL_Y_DIFF), parent->getLabelBackground(), "QUIT TO MAIN MENU");

	continueButton->setFontSize(MENU_LABEL_FONT_SIZE);
	quitToMainMenuButton->setFontSize(MENU_LABEL_FONT_SIZE);
	quitButton->setFontSize(MENU_LABEL_FONT_SIZE);

	this->addMenuItem(continueButton);
	this->addMenuItem(quitButton);
	this->addMenuItem(quitToMainMenuButton);
}

PauseMenu::~PauseMenu() {
	delete continueButton, quitButton, quitToMainMenuButton;
}

void PauseMenu::manageEvent(Event& e) {
	if (e.type == Event::MouseButtonPressed) {
		Label* l = getLabel(Vector2f(Mouse::getPosition() - parent->getPosition()));

		if (l == continueButton)
			AppModel::getInstance().unpauseGame();
		else if (l == quitButton) {
			AppModel::getInstance().closeGame();
			exit(0);
		}
		else if (l == quitToMainMenuButton)
			AppModel::getInstance().closeGame();
	}
	else if (e.type == Event::KeyPressed)
		if (e.key.code == Keyboard::Escape)
			AppModel::getInstance().unpauseGame();

}