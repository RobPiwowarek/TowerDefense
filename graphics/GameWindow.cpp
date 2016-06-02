#include "GameWindow.h"
#include "GameContent.h"
#include "../exceptions.h"
#include "../logic/Minion.h"
#include "../logic/Turret.h"
#include "../logic/WeaponFire.h"
#include "../logic/Item.h"
#include "../data/GameManager.h"
#include "menu/MainMenu.h"
#include "menu/PauseMenu.h"

using namespace graphics;
using namespace sf;
using namespace tower_defense;

#include <iostream>
using namespace std;

GameWindow::GameWindow() : RenderWindow(VideoMode(WINDOW_WIDTH, WINDOW_HEIGHT), "TowerDefense", sf::Style::None) {
	this->tm = new TextureManager();
	this->loadResources();
	this->loadingContent = new LoadingContent(this);
	this->mainMenu = new MainMenu(this);
	this->pauseMenu = new PauseMenu(this);
	cout << "Init finished\n";
}

const Font* GameWindow::getFont() const {
	return this->font;
}

void GameWindow::loadResources() {
	tm->add(graphics::TextureManager::MENU, LABEL_BACKGORUND_OID, LABEL_BACKGROUND);
	tm->add(graphics::TextureManager::MENU, PLACEHOLDER_TURRET_BACKGROUND_CAN_PLACE_OID, PLACEHOLDER_TURRET_BACKGROUND_CAN_PLACE);
	tm->add(graphics::TextureManager::MENU, PLACEHOLDER_TURRET_BACKGROUND_CANT_PLACE_OID, PLACEHOLDER_TURRET_BACKGROUND_CANT_PLACE);
	tm->add(graphics::TextureManager::MENU, VICTORY_TEXTURE_OID, VICTORY_TEXTURE);
	tm->add(graphics::TextureManager::MENU, DEFEAT_TEXTURE_OID, DEFEAT_TEXTURE);
	tm->add(graphics::TextureManager::MENU, MENU_BACKGROUND_OID, MENU_BACKGROUND);

	for (int i = 0; i < EXPLOSIONS_N; i++) {
		tm->add(graphics::TextureManager::EXPLOSION, i, EXPLOSIONS + to_string(i) + EXPLOSION_SUFFIX);
	}

	this->font = new sf::Font();
	if (!this->font->loadFromFile(FONT_LOCATION))
		NO_FONT_LOADED
}

const Texture* GameWindow::getDefeatTexture() const {
	return &this->tm->get(TextureManager::MENU, DEFEAT_TEXTURE_OID);
}

const Texture* GameWindow::getVictoryTexture() const {
	return &this->tm->get(TextureManager::MENU, VICTORY_TEXTURE_OID);
}

const Texture* GameWindow::getCanPlaceTurretBackground() const {
	return &this->tm->get(TextureManager::MENU, PLACEHOLDER_TURRET_BACKGROUND_CAN_PLACE_OID);
}

const Texture* GameWindow::getCantPlaceTurretBackground() const {
	return &this->tm->get(TextureManager::MENU, PLACEHOLDER_TURRET_BACKGROUND_CANT_PLACE_OID);
}

const Texture* GameWindow::getLabelBackground() const {
	return &this->tm->get(graphics::TextureManager::MENU, LABEL_BACKGORUND_OID);
}

const Texture* GameWindow::getTexture(const tower_defense::Minion* const m) const {
	return &this->tm->get(TextureManager::MINION, m->getObjClass());
}
const Texture* GameWindow::getTexture(const tower_defense::Turret* const t) const {
	return &this->tm->get(TextureManager::TURRET, t->getObjClass());
}
const Texture* GameWindow::getTexture(const tower_defense::WeaponFire* const w) const {
	return &this->tm->get(TextureManager::WEAPON_FIRE, w->getObjClass());
}
const Texture* GameWindow::getTexture(const tower_defense::Item* const i) const {
	return &this->tm->get(TextureManager::ITEM, i->getObjClass());
}

const Texture* GameWindow::getMapTexture(int x, int y) const {
	int id = AppModel::getInstance().getGameManager().get()->getTextureId(x, y);
	AppModel::getInstance().getGameManager().release();

	return &this->tm->get(TextureManager::MAP, id);
}

TextureManager* GameWindow::getTextureManager() {
	return this->tm;
}

void GameWindow::refresh() {
	while (true) {
		if (this->stopFlag) return;

		switch (AppModel::getInstance().getState()) {
		case AppModel::GameState::Loading:
			if (this->currentContent == (Content*)this->gameContent) {
				delete this->gameContent;
				this->gameContent = nullptr;
			}
			this->currentContent = (Content*)loadingContent;
			break;
		case AppModel::GameState::Going:
		case AppModel::GameState::Defeat:
		case AppModel::GameState::Victory:
			if (this->gameContent == nullptr)
				this->gameContent = new GameContent(*this);
			this->currentContent = gameContent;
			break;
		case AppModel::GameState::MainMenu:
			this->currentContent = this->mainMenu;
			if (this->gameContent != nullptr) {
				delete this->gameContent;
				this->gameContent = nullptr;
			}
			break;
		case AppModel::GameState::Paused:
			this->currentContent = this->pauseMenu;
		}

		this->currentContent->display();
		this->display();

		Event e;
		while (pollEvent(e)) {
			switch (e.type) {
			case Event::Closed:
				AppModel::getInstance().closeGame();
				this->close();
				return;
			default:
				this->currentContent->manageEvent(e);
			}
		}
		
		if (this->stopFlag) return;

		std::this_thread::sleep_for(std::chrono::milliseconds(20));
	}
}

GameWindow::~GameWindow() {
	this->stop();
	delete this->loadingContent;
	delete this->gameContent;
	delete this->mainMenu;
	delete this->pauseMenu;
}

void GameWindow::start() {
	while (!stopFlag)
		this->refresh();
}

void GameWindow::stop() {
	stopFlag = true;
}

const Texture* GameWindow::getMenuBackground() const {
	return &this->tm->get(TextureManager::MENU, MENU_BACKGROUND_OID);
}
const Texture* GameWindow::getExplosion() const {
	return &this->tm->get(TextureManager::EXPLOSION, rand() % EXPLOSIONS_N);
}
