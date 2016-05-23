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

	this->confirmLabel = new Label(Vector2f(FINISHED_LABEL_WIDTH, FINISHED_LABEL_HEIGHT),
		Vector2f(FINISHED_LABEL_X, FINISHED_LABEL_Y), AppModel::getInstance().getLabelBackground(), "Ok");
	this->confirmLabel->setFontSize(FINISHED_LABEL_FONT_SIZE);

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

Sprite& GameContent::getVictoryScreen(RenderWindow& w) {
	static Sprite* s = nullptr;
	if (s == nullptr) {
		s = new Sprite(*AppModel::getInstance().getVictoryTexture());
		s->setScale((float)w.getSize().x / s->getTexture()->getSize().x,
			(float)w.getSize().y / s->getTexture()->getSize().y);
	}
	return *s;
}
Sprite& GameContent::getDefeatScreen(RenderWindow& w) {
	static Sprite* s = nullptr;
	if (s == nullptr) {
		s = new Sprite(*AppModel::getInstance().getDefeatTexture());
		s->setScale((float)w.getSize().x / s->getTexture()->getSize().x,
			(float)w.getSize().y / s->getTexture()->getSize().y);
	}
	return *s;
}

void GameContent::refresh(RenderWindow& w) {
	Event e;
	while (w.pollEvent(e))
		this->manageEvent(e, w);

	this->checkKeys(w);

	this->displayer->refresh(w);



	switch (AppModel::getInstance().getState()) {
	case AppModel::GameState::Going:
		this->displayUI_game(w);
		break;
	case AppModel::GameState::Victory:
		w.draw(this->getVictoryScreen(w));

		this->displayUI_finished(w);
		break;
	case AppModel::GameState::Defeat:
		w.draw(this->getDefeatScreen(w));

		this->displayUI_finished(w);
		break;
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
	switch (AppModel::getInstance().getState()) {
	case AppModel::GameState::Going:
		this->manageEvent_mousePress_gameGoing(e, w);
		break;
	case AppModel::GameState::Victory:
	case AppModel::GameState::Defeat:
		this->manageEvent_mousePress_gameFinished(e, w);
		break;
	}
}
void GameContent::manageEvent_mousePress_gameFinished(Event& e, RenderWindow& w) {
	if (Mouse::getPosition().x >= FINISHED_LABEL_X && Mouse::getPosition().x <= FINISHED_LABEL_X + FINISHED_LABEL_WIDTH &&
		Mouse::getPosition().y >= FINISHED_LABEL_Y && Mouse::getPosition().y <= FINISHED_LABEL_Y + FINISHED_LABEL_HEIGHT);
}

void GameContent::manageEvent_mousePress_gameGoing(Event& e, RenderWindow& w) {

	int mouseX = sf::Mouse::getPosition().x - w.getPosition().x;
	int mouseY = sf::Mouse::getPosition().y - w.getPosition().y;

	Point inGame = displayer->screenToGame(w, Vector2f(mouseX, mouseY ));
	cout << "Mouse: (" << mouseX << ", " << mouseY << ") -> ( " << inGame.getX() << ", " << inGame.getY() << ")\n";

	int label = floor(((double)mouseY - TURRET_LABELS_Y) / TURRET_LABELS_Y_DIFF);
	if (mouseX >= TURRET_LABELS_X && mouseX <= TURRET_LABELS_X + TURRET_LABEL_WIDTH && label >= 0 && label < turretN) {
			this->selectedTurret = label != this->selectedTurret ? label : -1;
			if (this->selectedTurret == -1)
				this->displayer->setBuildingTurret(nullptr);
			else
				this->displayer->setBuildingTurret(&AppModel::getInstance().getTurretManager().get()->getTurret(selectedTurret));
			AppModel::getInstance().getTurretManager().release();
	}
	else if (selectedTurret != -1) {
		Point turLocation = this->displayer->getSelecetedTurretsLocation(w);
		std::cout << "Placing turret at (" << turLocation.getX() << ", " << turLocation.getY() << ")\n";

		AppModel::getInstance().getGame().get()->addTurret(
			&AppModel::getInstance().getTurretManager().get()->getTurret(selectedTurret),
			turLocation, this->turretList[selectedTurret].second.second);



		AppModel::getInstance().getTurretManager().release();
		AppModel::getInstance().getGame().release();
	}

	/*
	//MINION DEBUG
	if (inGame.getX() > 0 && inGame.getY() > 0)
		AppModel::getInstance().getGame().get()->getMap().addMinion(
		new Minion(AppModel::getInstance().getMinionManager().get()->getMinion(0), inGame));
		
	AppModel::getInstance().getGame().release();
	AppModel::getInstance().getMinionManager().release();
	*/
}

void graphics::GameContent::displayUI_game(RenderWindow& w) {
	Game* g = AppModel::getInstance().getGame().get();
	this->money->display(w, to_string(g->getPlayer().getMoney()));
	AppModel::getInstance().getGame().release();

	for (int i = 0; i < turretN; i++) {
		this->turretLabels[i]->display(w, "");
	}
}

void graphics::GameContent::displayUI_finished(RenderWindow& w) {
	this->confirmLabel->display(w, "");
}