#include "GameContent.h"
#include "../data/TurretManager.h"

using namespace graphics;
using namespace tower_defense;
using namespace sf;
using namespace std;

GameContent::GameContent(RenderWindow& w) {
	w.setSize({ WINDOW_WIDTH, WINDOW_HEIGHT });
	this->displayer = new GameDisplayer(Point(0, 0));
	this->money = new Label(Vector2f(MONEY_LABEL_WIDTH, MONEY_LABEL_HEIGHT),
		Vector2f(MONEY_LABEL_X, MONEY_LABEL_Y), AppModel::getInstance().getLabelBackground(), "$:");
	this->money->setFontSize(MONEY_LABEL_FONT_SIZE);
	this->createTurretList();
}
#include <iostream>
void GameContent::createTurretList() {
	AppModel::getInstance().getTurretManager().get()->getTurrets(this->turretList);
	AppModel::getInstance().getTurretManager().release();

	this->turretLabels = new Label*[this->turretN = this->turretList.size()];
	for (int i = 0;	i < turretN; i++) {
		this->turretLabels[i] = new Label(Vector2f(TURRET_LABEL_WIDTH, TURRET_LABEL_HEIGHT),
			Vector2f(TURRET_LABELS_X, TURRET_LABELS_Y + TURRET_LABELS_Y_DIFF * i),
			AppModel::getInstance().getLabelBackground(),
			this->turretList[i].second.first + ": " + to_string(this->turretList[i].second.second) + "$");
		cout << this->turretList[i].second.first + ": " + to_string(this->turretList[i].second.second) + "$" << endl;
		this->turretLabels[i]->setFontSize(TURRET_LABEL_FONT_SIZE);
	}
}

void GameContent::display(RenderWindow& w) {
	this->displayer->refresh(w);
	Game* g = AppModel::getInstance().getGame().get();
	this->money->display(w, to_string(g->getPlayer().getMoney()));
	AppModel::getInstance().getGame().release();

	for (int i = 0; i < turretN; i++) {
		this->turretLabels[i]->display(w, "");
	}
}

GameContent::~GameContent() {
	delete this->displayer;
	delete this->money;

	for (int i = 0; i < turretN; i++)
		delete this->turretLabels[i];
	delete[] this->turretLabels;
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