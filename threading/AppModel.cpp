#include <exception>

#include "AppModel.h"
#include "ResourceManager.h"
#include "..\graphics\TextureManager.h"
#include "..\data\MinionManager.h"
#include "..\data\GameManager.h"
#include "..\data\MinionWaveManager.h"

AppModel& AppModel::getInstance() {
	static std::mutex instanceLocker;
	instanceLocker.lock();
	static AppModel instance;
	instanceLocker.unlock();

	return instance;
}

ResourceManager<tower_defense::Game>& AppModel::getGame() {
	if (this->game == nullptr)
		throw std::exception("Game was not initialized!");

	return *this->game;
}
ResourceManager<Refresher>& AppModel::getRefresher() {
	if (this->refresher == nullptr)
		throw std::exception("Game was not initialized!");

	return *this->refresher;
}

ResourceManager<graphics::TextureManager>& AppModel::getTextures() {
	return *this->textureManager;
}

ResourceManager<data::MinionManager>& AppModel::getMinionManager() {
	return *this->minionManager;
}
ResourceManager<data::MinionWaveManager>& AppModel::getMinionWaveManager() {
	return *this->minionWaveManager;
}

ResourceManager<data::GameManager>& AppModel::getGameManager() {
	return *this->gameManager;
}

AppModel::~AppModel() {
	delete this->game;
	delete this->refresher;

	delete this->textureManager;
}

AppModel::AppModel() {
	this->game = nullptr;
	this->refresher = nullptr;

	this->textureManager = new ResourceManager<graphics::TextureManager>(new graphics::TextureManager);
	this->minionManager = new ResourceManager<data::MinionManager>(new data::MinionManager);
	this->gameManager = new ResourceManager<data::GameManager>(new data::GameManager);
	this->minionWaveManager = new ResourceManager<data::MinionWaveManager>(new data::MinionWaveManager);
}