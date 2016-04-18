#ifndef GAME_MANAGER_H
#define GAME_MANAGER_H

namespace data {
	class GameManager;
}

#include <map>
#include "../logic/Game.h"
#include "../include/SFML/Graphics.hpp"
#include "../include/pugixml/pugixml.hpp"

namespace data {
	class GameManager {
	public:
		// clear all data (also from other managers)
		void clear();
		// load game (also other managers) from xml at given path
		tower_defense::Game* load(const std::string& path);
		// returns texture of the map tile (square of size 1)
		// at given coordinates
		const sf::Texture& getMapTexture(int x, int y) const;

		~GameManager();
	private:
		tower_defense::Map* loadMap(const std::string& directory, const pugi::xml_node& map);
		tower_defense::Player* loadPlayer(const std::string& directory, const pugi::xml_node& player);

		int mapSize;
		int playerAreaSize;
		std::map<std::pair<int, int>, std::string> mapTextures;
	};
}

#endif