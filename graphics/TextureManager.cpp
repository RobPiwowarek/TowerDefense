#include "TextureManager.h"

#include <limits>
#include <exception>

#define OBJ_ID_OVERFLOW(x) throw std::exception(("Exception: Object identificator overflow: " + std::to_string(x)).c_str());
#define UNSIGNED_INTEGER_TO_SMALL throw std::exception("Exception: Unsigned integer is too small for textures");
#define TEXTURE_LOADING_FAILIURE(x) throw std::exception(("Exception: Failed to load texture:\n\t" + std::string(x)).c_str());
#define TEXTURE_DOES_NOT_EXISIT throw std::exception("Exception: Failed to get a texture");

#ifdef LOAD_TEST
#include <iostream> 
#include <bitset>
#endif

unsigned int graphics::TextureManager::add(const unsigned int flag, const unsigned int objId, const std::string& path) {
	if (objId >> objIdShift)
		OBJ_ID_OVERFLOW(objId)

	const unsigned int id = this->id(flag, objId);

	if (this->textures.find(id) == this->textures.end()) {
		sf::Texture* t = new sf::Texture();
		if (t->loadFromFile(path)) {
			((id & BASE) ? this->baseTextures[id] : this->textures[id]) = t;
#ifdef LOAD_TEST
			std::cout << std::bitset<sizeof id * 8>(id) << std::endl;
#endif
		}
		else {
			delete t;
			TEXTURE_LOADING_FAILIURE(path)
		}
	}

	return id;
}

void graphics::TextureManager::clear() {
	for (std::map<unsigned int, sf::Texture*>::iterator it = this->textures.begin();
		it != this->textures.end(); it++) {
		delete it->second;
	}
	this->textures.clear();
}

const sf::Texture& graphics::TextureManager::get(const unsigned int flag, const unsigned int objId) const {
	if (objId << -objIdShift)
		OBJ_ID_OVERFLOW(objId)

	return this->get(id(flag, objId));
}

const sf::Texture& graphics::TextureManager::get(const unsigned int id) const {
	const std::map<unsigned int, sf::Texture*>& textures = (id & BASE ? this->baseTextures : this->textures);

	std::map<unsigned int, sf::Texture*>::const_iterator it = textures.find(id);
	if (it == textures.end())
		TEXTURE_DOES_NOT_EXISIT

	return *it->second;
}

graphics::TextureManager::~TextureManager() {
	this->clear();
	for (std::map<unsigned int, sf::Texture*>::iterator it = this->baseTextures.begin();
		it != this->baseTextures.end(); it++)
		delete it->second;
}

graphics::TextureManager::TextureManager() {
	if (sizeof(unsigned int) * 8 <= FLAGS)
		UNSIGNED_INTEGER_TO_SMALL

	this->objIdShift = sizeof(unsigned int) * 8 - FLAGS;
}

unsigned int graphics::TextureManager::id(unsigned int flag, unsigned int objId) const {
	return objId << objIdShift | flag;
}