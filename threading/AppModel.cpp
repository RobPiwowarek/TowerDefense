#include "AppModel.h"
#include "ResourceManager.h"
#include "Refresher.h"
#include "..\logic\Game.h"
#include "..\graphics\TextureManager.h"
#include "..\data\MinionManager.h"
#include "..\data\GameManager.h"
#include "..\data\MinionWaveManager.h"
#include "..\data\TurretManager.h"
#include "..\data\WeaponFireManager.h"
#include "..\exceptions.h"

AppModel &AppModel::getInstance() {
    static std::mutex instanceLocker;
    instanceLocker.lock();
    static AppModel instance;
    instanceLocker.unlock();

    return instance;
}

ResourceManager<tower_defense::Game> &AppModel::getGame() {
    if (this->game == nullptr)
        throw std::exception("Game was not initialized!");

    return *this->game;
}

ResourceManager<Refresher> &AppModel::getRefresher() {
    if (this->refresher == nullptr)
        throw std::exception("Game was not initialized!");

    return *this->refresher;
}

ResourceManager<graphics::TextureManager> &AppModel::getTextures() {
    return *this->textureManager;
}

ResourceManager<data::MinionManager> &AppModel::getMinionManager() {
    return *this->minionManager;
}

ResourceManager<data::MinionWaveManager> &AppModel::getMinionWaveManager() {
	return *this->minionWaveManager;
}
ResourceManager<data::TurretManager> &AppModel::getTurretManager() {
	return *this->turretManager;
}
ResourceManager<data::WeaponFireManager>& AppModel::getWeaponFireManager() {
	return *this->weaponFireManager;
}

ResourceManager<data::GameManager> &AppModel::getGameManager() {
    return *this->gameManager;
}

AppModel::~AppModel() {
    delete this->game;
    delete this->refresher;

    delete this->textureManager;
	delete this->minionManager;
	delete this->minionWaveManager;
	delete this->turretManager;
	delete this->weaponFireManager;
	delete this->gameManager;
}

AppModel::AppModel() {
    this->game = nullptr;
    this->refresher = nullptr;

	this->textureManager = new ResourceManager<graphics::TextureManager>(new graphics::TextureManager);
	this->minionManager = new ResourceManager<data::MinionManager>(new data::MinionManager);
	this->gameManager = new ResourceManager<data::GameManager>(new data::GameManager);
	this->minionWaveManager = new ResourceManager<data::MinionWaveManager>(new data::MinionWaveManager);
	this->turretManager = new ResourceManager<data::TurretManager>(new data::TurretManager);
	this->weaponFireManager = new ResourceManager<data::WeaponFireManager>(new data::WeaponFireManager);

	this->loadResources();
}

bool AppModel::createGame(const std::string& xmlURI) {
	bool r = false;
	try {
		this->game = new ResourceManager<tower_defense::Game>(this->gameManager->get()->load(xmlURI));
		r = true;
		this->gameManager->release();
	}
	catch (std::exception e) {
		if (!r)
			this->gameManager->release();
		this->closeGame();
		return false;
	}

	return true;
}

void AppModel::closeGame() {
	delete this->refresher;
	this->refresher = nullptr;
	delete this->game;
	this->game = nullptr;

	this->gameManager->get()->clear();
	this->gameManager->release();

	this->minionManager->get()->clear();
	this->minionManager->release();
	this->minionWaveManager->get()->clear();
	this->minionWaveManager->release();
	this->textureManager->get()->clear();
	this->textureManager->release();
	this->turretManager->get()->clear();
	this->turretManager->release();
}


const sf::Font* AppModel::getFont() {
	return this->font;
}

void AppModel::loadResources() {
	this->textureManager->get()->add(graphics::TextureManager::MENU, LABEL_BACKGORUND_OID, LABEL_BACKGROUND);
	this->textureManager->release();

	this->font = new sf::Font();
	if (!this->font->loadFromFile(FONT_LOCATION))
		NO_FONT_LOADED
}

const sf::Texture* AppModel::getLabelBackground() {
	const sf::Texture* toRet = &this->textureManager->get()->get(graphics::TextureManager::MENU, LABEL_BACKGORUND_OID);
	this->textureManager->release();

	return toRet;
}