#include "TextureManager.h"

void graphics::TextureManager::add(std::string name) {
	if (this->textures.find(name) == this->textures.end()) {
		sf::Texture* t = new sf::Texture();
		if (t->loadFromFile(name))
			this->textures[name] = t;
		else delete t;
	}
}

void graphics::TextureManager::add_base(std::string name) {
	if (this->textures_base.find(name) == this->textures_base.end()) {
		sf::Texture* t = new sf::Texture();
		if (t->loadFromFile(name))
			this->textures[name] = t;
		else delete t;
	}
}

void graphics::TextureManager::clear() {
	for (std::map<std::string, sf::Texture*>::iterator it = this->textures.begin();
		it != this->textures.end(); it++) {
		delete it->second;
	}
	this->textures.clear();
}

const sf::Texture& graphics::TextureManager::get(std::string name) const {
	std::map<std::string, sf::Texture*>::const_iterator it = this->textures.find(name);
	if (it != this->textures.end())
		return *it->second;
	it = this->textures_base.find(name);

	return *it->second;
}

graphics::TextureManager::~TextureManager() {
	this->clear();
	for (std::map<std::string, sf::Texture*>::iterator it = this->textures_base.begin();
		it != this->textures_base.end(); it++)
		delete it->second;
}