#include "GameContent.h"
#include "../data/TurretManager.h"
#include "../data/MinionManager.h"

using namespace graphics;
using namespace tower_defense;
using namespace sf;
using namespace std;

GameContent::GameContent(GameWindow& w) : Content(&w) {
	this->displayer = new GameDisplayer(Point(0, 0));

	this->money = new Label(Vector2f(MONEY_LABEL_WIDTH, MONEY_LABEL_HEIGHT),
		Vector2f(MONEY_LABEL_X, MONEY_LABEL_Y), w.getLabelBackground(), "$:");
	this->money->setFontSize(MONEY_LABEL_FONT_SIZE);

	this->confirmLabel = new Label(Vector2f(FINISHED_LABEL_WIDTH, FINISHED_LABEL_HEIGHT),
		Vector2f(FINISHED_LABEL_X, FINISHED_LABEL_Y), w.getLabelBackground(), "Ok");
	this->confirmLabel->setFontSize(FINISHED_LABEL_FONT_SIZE);

	this->createTurretList();

	for (bool b : this->keys)
		b = false;
}

#include <iostream>
void GameContent::createTurretList() {
	AppModel::getInstance().getTurretManager().get()->getTurrets(this->turretList);
	AppModel::getInstance().getTurretManager().release();

	this->turretLabels = new Label*[this->turretN = this->turretList.size()];
	for (int i = 0;	i < turretN; i++) {
		this->turretLabels[i] = new Label(Vector2f(TURRET_LABEL_WIDTH, TURRET_LABEL_HEIGHT),
			Vector2f(TURRET_LABELS_X, TURRET_LABELS_Y + TURRET_LABELS_Y_DIFF * i),
			this->parent->getLabelBackground(),
			this->turretList[i].second.first + ": " + to_string(this->turretList[i].second.second) + "$");
		this->turretLabels[i]->setFontSize(TURRET_LABEL_FONT_SIZE);
	}
}

Sprite& GameContent::getVictoryScreen() {
	static Sprite* s = nullptr;
	if (s == nullptr) {
		s = new Sprite(*this->parent->getVictoryTexture());
		s->setScale((float)this->parent->getSize().x / s->getTexture()->getSize().x,
			(float)this->parent->getSize().y / s->getTexture()->getSize().y);
	}
	return *s;
}
Sprite& GameContent::getDefeatScreen() {
	static Sprite* s = nullptr;
	if (s == nullptr) {
		s = new Sprite(*this->parent->getDefeatTexture());
		s->setScale((float)this->parent->getSize().x / s->getTexture()->getSize().x,
			(float)this->parent->getSize().y / s->getTexture()->getSize().y);
	}
	return *s;
}

void GameContent::display() {
	this->checkKeys();

	this->displayer->refresh(*this->parent);

	switch (AppModel::getInstance().getState()) {
	case AppModel::GameState::Going:
		this->displayUI_game(*this->parent);
		break;
	case AppModel::GameState::Victory:
		this->parent->draw(this->getVictoryScreen());

		this->displayUI_finished();
		break;
	case AppModel::GameState::Defeat:
		this->parent->draw(this->getDefeatScreen());

		this->displayUI_finished();
		break;
	}
}

GameContent::~GameContent() {
	delete this->displayer;
	delete this->money;

	for (int i = 0; i < turretN; i++)
		delete this->turretLabels[i];
	delete[] this->turretLabels;
}

void GameContent::manageEvent(sf::Event& e) {
	switch (e.type) {
	case sf::Event::KeyPressed:
		keys[e.key.code] = true;
		break;
	case sf::Event::KeyReleased:
		keys[e.key.code] = false;
		break;
	case sf::Event::MouseButtonPressed:
		this->manageEvent_mousePress(e);
		break;
	}
}

void GameContent::checkKeys() {
	if (keys[sf::Keyboard::PageUp])
		this->displayer->setPointsPerUnit(this->displayer->getPointsPerUnit() * 3 / 2);
	if (keys[sf::Keyboard::PageDown])
		this->displayer->setPointsPerUnit(this->displayer->getPointsPerUnit() * 2 / 3);
	if (keys[sf::Keyboard::Up] || keys[sf::Keyboard::W])
		this->displayer->moveScreen(tower_defense::Point(0.0, -10.0 / this->displayer->getPointsPerUnit()));
	if (keys[sf::Keyboard::Down] || keys[sf::Keyboard::S])
		this->displayer->moveScreen(tower_defense::Point(0.0, 10.0 / this->displayer->getPointsPerUnit()));
	if (keys[sf::Keyboard::Left] || keys[sf::Keyboard::A])
		this->displayer->moveScreen(tower_defense::Point(-10.0 / this->displayer->getPointsPerUnit(), 0.0));
	if (keys[sf::Keyboard::Right] || keys[sf::Keyboard::D])
		this->displayer->moveScreen(tower_defense::Point(10.0 / this->displayer->getPointsPerUnit(), 0.0));
	if (keys[sf::Keyboard::Escape] && AppModel::getInstance().getState() == AppModel::GameState::Going) {
		AppModel::getInstance().pauseGame();
		for (int i = 0; i < Keyboard::KeyCount; i++)
			keys[i] = false;
	}
}

void GameContent::manageEvent_mousePress(Event& e) {
	switch (AppModel::getInstance().getState()) {
	case AppModel::GameState::Going:
		this->manageEvent_mousePress_gameGoing(e);
		break;
	case AppModel::GameState::Victory:
	case AppModel::GameState::Defeat:
		this->manageEvent_mousePress_gameFinished(e);
		break;
	}
}
void GameContent::manageEvent_mousePress_gameFinished(Event& e) {
	Vector2i mousePos = Mouse::getPosition() - parent->getPosition();
	if (mousePos.x >= FINISHED_LABEL_X && mousePos.x <= FINISHED_LABEL_X + FINISHED_LABEL_WIDTH &&
		mousePos.y >= FINISHED_LABEL_Y && mousePos.y <= FINISHED_LABEL_Y + FINISHED_LABEL_HEIGHT)
		AppModel::getInstance().closeGame();
}

void GameContent::manageEvent_mousePress_gameGoing(Event& e) {

	int mouseX = sf::Mouse::getPosition().x - this->parent->getPosition().x;
	int mouseY = sf::Mouse::getPosition().y - this->parent->getPosition().y;

	Point inGame = displayer->screenToGame(*this->parent, Vector2f(mouseX, mouseY));

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
		if (e.mouseButton.button != Mouse::Button::Left) {
			this->selectedTurret = -1;
			this->displayer->setBuildingTurret(nullptr);
		}
		else {
			Point turLocation = this->displayer->getSelecetedTurretsLocation(*this->parent);

			AppModel::getInstance().getGame().get()->addTurret(
				&AppModel::getInstance().getTurretManager().get()->getTurret(selectedTurret),
				turLocation, this->turretList[selectedTurret].second.second);

			AppModel::getInstance().getTurretManager().release();
			AppModel::getInstance().getGame().release();
		}
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


void graphics::GameContent::displayUI_game(GameWindow& w) {
	Game* g = AppModel::getInstance().getGame().get();
	this->money->display(w, to_string(g->getPlayer().getMoney()));
	AppModel::getInstance().getGame().release();

	for (int i = 0; i < turretN; i++) {
		this->turretLabels[i]->display(*this->parent, "");
	}
}

void graphics::GameContent::displayUI_finished() {
	this->confirmLabel->display(*this->parent, "");
}