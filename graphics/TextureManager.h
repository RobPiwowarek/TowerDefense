#ifndef TEXTURE_MANAGER_H
#define TEXTURE_MANAGER_H

#include <string>
#include <map>

#include "../include/SFML/Graphics.hpp"


namespace graphics {
	class TextureManager {
	private:
		static const unsigned int FLAGS = 6;
	public:
		static const unsigned int WEAPON_FIRE = 1 << 5;
		static const unsigned int ITEM = 1 << 4;
		static const unsigned int MAP = 1 << 3;
		static const unsigned int TURRET = 1 << 2;
		static const unsigned int MINION = 1 << 1;
		static const unsigned int MENU = 1;

		const unsigned int BASE = MENU;

		// adds texture from image file to the manager
		unsigned int add(const unsigned int flag, const unsigned int objId, const std::string& path);
		// removes all textures from manager except base
		void clear();
		// returns texture with given name
		// with base at lower priority
		const sf::Texture& get(const unsigned int id) const;
		const sf::Texture& get(const unsigned int flag, const unsigned int objId) const;

		TextureManager();
		~TextureManager();
	private:
		int flagsShift;

		std::map<unsigned int, sf::Texture*> baseTextures;
		std::map<unsigned int, sf::Texture*> textures;
	};
}

#endif