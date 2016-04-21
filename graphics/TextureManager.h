#ifndef TEXTURE_MANAGER_H
#define TEXTURE_MANAGER_H

#include <string>
#include <map>

#include "../include/SFML/Graphics.hpp"


namespace graphics {
	class TextureManager {
	public:
		// adds texture from image file to the manager
		void add(const std::string& name, const std::string& path);
		// adds texture from image file to the manager
		void add_base(const std::string& name, const std::string& path);
		// removes all textures from manager except base
		void clear();
		// returns texture with given name
		// with base at lower priority
		const sf::Texture& get(const std::string& name) const;
		~TextureManager();
	private:
		std::map<std::string, sf::Texture*> textures_base;
		std::map<std::string, sf::Texture*> textures;
	};
}

#endif