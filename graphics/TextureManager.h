#ifndef TEXTURE_MANAGER_H
#define TEXTURE_MANAGER_H

#include <string>
#include <map>

#include "../include/SFML/Graphics.hpp"


namespace graphics {
	class TextureManager {
	public:
		// adds texture from image file to the manager
		void add(std::string name);
		// adds texture from image file to the manager
		void add_base(std::string name);
		// removes all textures from manager except base
		void clear();
		// returns texture with given name
		// with base at lower priority
		const sf::Texture& get(std::string name) const;
		~TextureManager();
	private:
		std::map<std::string, sf::Texture*> textures_base;
		std::map<std::string, sf::Texture*> textures;
	};
}

#endif