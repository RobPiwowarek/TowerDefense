#include <exception>

#include "AppModel.h"
#include "ResourceManager.h"
#include "..\graphics\TextureManager.h"

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

AppModel::~AppModel() {
	delete this->game;
	delete this->refresher;

	delete this->textureManager;
}

AppModel::AppModel() {
	this->game = nullptr;
	this->refresher = nullptr;

	this->textureManager = new ResourceManager<graphics::TextureManager>(new graphics::TextureManager);
}