#include "TextureManager.h"

#define LOAD_TEST

#include <limits>

#include "../exceptions.h"
#ifdef LOAD_TEST
#include <iostream> 
#include <bitset>
#endif

unsigned int graphics::TextureManager::add(const unsigned int flag, const unsigned int objId, const std::string& path) {

	const unsigned int id = this->id(flag, objId);

#ifdef LOAD_TEST
	if (id & WEAPON_FIRE) std::cout << "loading texture: " << path << std::endl;
#endif

	if (this->textures.find(id) == this->textures.end()) {
		sf::Texture* t = new sf::Texture();
		if (t->loadFromFile(path)) {
			((id & BASE) ? this->baseTextures[id] : this->textures[id]) = t;
#ifdef LOAD_TEST
			if (id & WEAPON_FIRE) 		std::cout << "Texture loaded as " << std::bitset<sizeof id * 8>(id) << std::endl;
#endif
		}
		else {
			delete t;
			TEXTURE_LOADING_FAILIURE(path)
		}
	}

	return objId;
}

void graphics::TextureManager::clear() {
    for (std::map<unsigned int, sf::Texture *>::iterator it = this->textures.begin();
         it != this->textures.end(); it++) {
        delete it->second;
    }
    this->textures.clear();
}

const sf::Texture& graphics::TextureManager::get(const unsigned int flag, const unsigned int objId) const {

	return this->get(id(flag, objId));
}

const sf::Texture &graphics::TextureManager::get(const unsigned int id) const {
    const std::map<unsigned int, sf::Texture *> &textures = (id & BASE ? this->baseTextures : this->textures);
    std::map<unsigned int, sf::Texture *>::const_iterator it = textures.find(id);
	if (it == textures.end()){
		TEXTURE_DOES_NOT_EXISIT
	}

    return *it->second;
}

graphics::TextureManager::~TextureManager() {
    this->clear();
    for (std::map<unsigned int, sf::Texture *>::iterator it = this->baseTextures.begin();
         it != this->baseTextures.end(); it++)
        delete it->second;
}

graphics::TextureManager::TextureManager() {
	if (sizeof(unsigned int) * 8 <= FLAGS)
		UNSIGNED_INTEGER_TO_SMALL

	this->objIdShift = FLAGS;
}

unsigned int graphics::TextureManager::id(unsigned int flag, unsigned int objId) const {
	return objId << objIdShift | flag;
}