#include "GameContent.h"
#include "../data/TurretManager.h"
#include "../data/MinionManager.h"

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

	for (bool b : this->keys)
		b = false;

	this->debugL = new Label({ 150, 20 }, { 0, 580 }, AppModel::getInstance().getLabelBackground(), "selected turret: ");
	this->debugL->setFontSize(15);
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

void GameContent::refresh(RenderWindow& w) {
	Event e;
	while (w.pollEvent(e))
		this->manageEvent(e, w);

	this->checkKeys(w);

	this->displayer->refresh(w);

	Game* g = AppModel::getInstance().getGame().get();
	this->money->display(w, to_string(g->getPlayer().getMoney()));
	AppModel::getInstance().getGame().release();

	for (int i = 0; i < turretN; i++) {
		this->turretLabels[i]->display(w, "");
	}

	this->debugL->display(w, to_string(this->selectedTurret));
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
	case sf::Event::Closed:
		w.close();
		break;
	case sf::Event::KeyPressed:
		keys[e.key.code] = true;
		break;
	case sf::Event::KeyReleased:
		keys[e.key.code] = false;
		break;
	case sf::Event::MouseButtonPressed:
		this->manageEvent_mousePress(e, w);
		break;
	}
}

void GameContent::checkKeys(sf::RenderWindow& w) {
	if (keys[sf::Keyboard::PageUp])
		this->displayer->setPointsPerUnit(this->displayer->getPointsPerUnit() * 3 / 2);
	if (keys[sf::Keyboard::PageDown])
		this->displayer->setPointsPerUnit(this->displayer->getPointsPerUnit() * 2 / 3);
	if (keys[sf::Keyboard::Up])
		this->displayer->moveScreen(tower_defense::Point(0, -10.0 / this->displayer->getPointsPerUnit()));
	if (keys[sf::Keyboard::Down])
		this->displayer->moveScreen(tower_defense::Point(0, 10.0 / this->displayer->getPointsPerUnit()));
	if (keys[sf::Keyboard::Left])
		this->displayer->moveScreen(tower_defense::Point(-10.0 / this->displayer->getPointsPerUnit(), 0));
	if (keys[sf::Keyboard::Right])
		this->displayer->moveScreen(tower_defense::Point(10.0 / this->displayer->getPointsPerUnit(), 0));
}

void GameContent::manageEvent_mousePress(Event& e, RenderWindow& w) {
	int mouseX = sf::Mouse::getPosition().x - w.getPosition().x;
	int mouseY = sf::Mouse::getPosition().y - w.getPosition().y;

	Point inGame = displayer->screenToGame(w, Vector2f(mouseX, mouseY ));
	cout << "Mouse: (" << mouseX << ", " << mouseY << ") -> ( " << inGame.getX() << ", " << inGame.getY() << ")\n";

	int label = floor(((double)mouseY - TURRET_LABELS_Y) / TURRET_LABELS_Y_DIFF);
	if (mouseX >= TURRET_LABELS_X && mouseX <= TURRET_LABELS_X + TURRET_LABEL_WIDTH && label >= 0 && label < turretN) {
			this->selectedTurret = label != this->selectedTurret ? label : -1;
			this->displayer->setBuildingTurret(&AppModel::getInstance().getTurretManager().get()->getTurret(selectedTurret));
			AppModel::getInstance().getTurretManager().release();
	}
	else if (selectedTurret != -1) {
		Point turLocation = this->displayer->getSelecetedTurretsLocation(w);
		std::cout << "Placing turret at (" << turLocation.getX() << ", " << turLocation.getY() << "): ";

		std::cout <<
			AppModel::getInstance().getGame().get()->getMap().canPlaceTurret(turLocation,
			AppModel::getInstance().getTurretManager().get()->getTurret(this->selectedTurret)) << endl;

		AppModel::getInstance().getTurretManager().release();
		AppModel::getInstance().getGame().release();
	}


	//MINION DEBUG
	if (inGame.getX() > 0 && inGame.getY() > 0)
		AppModel::getInstance().getGame().get()->getMap().addMinion(
		new Minion(AppModel::getInstance().getMinionManager().get()->getMinion(0), inGame));

	AppModel::getInstance().getGame().release();
	AppModel::getInstance().getMinionManager().release();
}