#include "GameContent.h"

using namespace graphics;
using namespace tower_defense;
using namespace sf;
using namespace std;

GameContent::GameContent() {
	this->displayer = new GameDisplayer(Point(0, 0));
	this->money = new Label(Vector2f(100, 25), Vector2f(10, 10), AppModel::getInstance().getLabelBackground(), "$:");
	this->money->setFontSize(20);
}

void GameContent::display(RenderWindow& w) {
	this->displayer->refresh(w);
	Game* g = AppModel::getInstance().getGame().get();
	this->money->display(w, to_string(g->getPlayer().getMoney()));
	AppModel::getInstance().getGame().release();
}

GameContent::~GameContent() {
	delete this->displayer;
	delete this->money;
}

void GameContent::manageEvent(sf::Event& e, sf::RenderWindow& w) {
	switch (e.type) {
	case sf::Event::KeyPressed:
		this->manageEvent_KeyPressed(e, w);
		break;
	}
}

void GameContent::manageEvent_KeyPressed(sf::Event& e, sf::RenderWindow& w) {
	switch (e.key.code) {
	case sf::Keyboard::PageUp:
		this->displayer->setPointsPerUnit(this->displayer->getPointsPerUnit() * 3 / 2);
		break;
	case sf::Keyboard::PageDown:
		this->displayer->setPointsPerUnit(this->displayer->getPointsPerUnit() * 2 / 3);
		break;
	case sf::Keyboard::Up:
		this->displayer->moveScreen(tower_defense::Point(0, -10.0 / this->displayer->getPointsPerUnit()));
		break;
	case sf::Keyboard::Down:
		this->displayer->moveScreen(tower_defense::Point(0, 10.0 / this->displayer->getPointsPerUnit()));
		break;
	case sf::Keyboard::Left:
		this->displayer->moveScreen(tower_defense::Point(-10.0 / this->displayer->getPointsPerUnit(), 0));
		break;
	case sf::Keyboard::Right:
		this->displayer->moveScreen(tower_defense::Point(10.0 / this->displayer->getPointsPerUnit(), 0));
		break;
	}
}