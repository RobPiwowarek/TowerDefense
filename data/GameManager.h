#ifndef GAME_MANAGER_H
#define GAME_MANAGER_H

namespace data {
    class GameManager;
}

#include <map>
#include "../logic/Game.h"
#include "../graphics/TextureManager.h"
#include "../include/SFML/Graphics.hpp"
#include "../include/pugixml/pugixml.hpp"

namespace data {
    class GameManager {
    public:
        // clear all data
        void clear();

        // load game (also other managers) from xml at given path
		tower_defense::Game *load(const std::string &path, graphics::TextureManager* tm);

		// returns id of the texture of map field at given coordinates
		unsigned int GameManager::getTextureId(int x, int y) const;
        ~GameManager();

	private:
		const std::string MAP_TEXTURES_LOCATION = "map\\";
		const std::string ITEM_TEXTURES_LOCATION = "items\\";

        tower_defense::Map *loadMap(const std::string &directory, const pugi::xml_node &map, graphics::TextureManager* tm);

        tower_defense::Player *loadPlayer(const std::string &directory, const pugi::xml_node &player, graphics::TextureManager* tm);

		void loadWaves(const std::string &directory, const pugi::xml_node &waves, graphics::TextureManager* tm);
		void loadTurrets(const std::string &directory, const pugi::xml_node &turrets, graphics::TextureManager* tm);

		// returns number of loaded items
		int loadItems(const std::string &directory, const pugi::xml_node &game, tower_defense::Map* map, graphics::TextureManager* tm);

        int mapSize;
        int playerAreaSize;
        std::map<std::pair<int, int>, unsigned int> mapTextures;

		inline tower_defense::Point randPoint() const;
    };
}

#endif