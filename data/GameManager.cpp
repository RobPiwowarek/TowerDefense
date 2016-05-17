#include "GameManager.h"
#include "MinionWaveManager.h"
#include "MinionManager.h"
#include "TurretManager.h"

#include "../threading/AppModel.h"
#include "../threading/ResourceManager.h"
#include "../graphics/TextureManager.h"

#include "../include/pugixml/pugixml.hpp"

#include <cstdlib>

#include "../exceptions.h"



using namespace data;
using namespace tower_defense;
using namespace std;
using namespace sf;

void GameManager::clear() {
	this->mapTextures.clear();
}

#include <iostream>

Game *GameManager::load(const string &path) {
    string directory = path;
    for (int i = directory.size() - 1; i >= 0; i--) {
        if (directory[i] == '/' || directory[i] == '\\') {
            directory = path.substr(0, i + 1);
            break;
        }
    }

    Map *map;
    Player *player;


    pugi::xml_document gameDoc;
    pugi::xml_parse_result result = gameDoc.load_file(path.c_str(),
		pugi::parse_full | pugi::parse_trim_pcdata, pugi::encoding_utf8);

	if (result.status != pugi::status_ok) {
		std::cout << '[' << result.status << ']';
		FAILED_TO_LOAD_GAME
	}

    pugi::xml_node game = gameDoc.child("game");

    map = loadMap(directory, game.child("map"));
    player = loadPlayer(directory, game.child("player"));

    loadWaves(directory, game.child("waves"));

	player->setNItems(loadItems(directory, game, map));

    return new Game(map, player);
}


const Texture& GameManager::getMapTexture(int x, int y) const {
	if (x >= this->mapSize || y >= this->mapSize || x < 0 || y < 0)
		POINT_OUT_OF_MAP(x, y)

    const Texture &toRet = AppModel::getInstance().getTextures().get()->get(
            this->mapTextures.find(make_pair(x, y))->second);
    AppModel::getInstance().getTextures().release();

    return toRet;
}

const Texture& GameManager::getItemTexture(int objClass) const {
	const Texture &toRet = AppModel::getInstance().getTextures().get()->get(graphics::TextureManager::ITEM, objClass);
	AppModel::getInstance().getTextures().release();

	return toRet;
}

Map *GameManager::loadMap(const string &directory, const pugi::xml_node &map) {
    graphics::TextureManager *textureManager = AppModel::getInstance().getTextures().get();

    std::map<string, unsigned int> loadedTextures;

    this->mapSize = atoi(map.child("size").child_value());
	this->playerAreaSize = atoi(map.child_value("playerarea"));

    pugi::xml_object_range<pugi::xml_named_node_iterator> textures = map.children("texture");

    for (pugi::xml_named_node_iterator it = textures.begin(); it != textures.end(); it++) {
        int x, y;

        x = it->attribute("x").as_int();
        y = it->attribute("y").as_int();

        string texture = it->child_value();
        if (loadedTextures[texture])
            this->mapTextures[make_pair(x, y)] = loadedTextures[texture];
        else
            this->mapTextures[make_pair(x, y)] = loadedTextures[texture] =
                    textureManager->add(graphics::TextureManager::MAP, loadedTextures.size() - 1,
                                        directory + MAP_TEXTURES_LOCATION + texture);
    }

    AppModel::getInstance().getTextures().release();

    return new Map(this->mapSize, this->mapSize);
}

Player *GameManager::loadPlayer(const std::string &directory, const pugi::xml_node &player) {
	loadTurrets(directory, player.child("turrets"));
    return new Player(atoi(player.child("startingMoney").child_value()));
}

void GameManager::loadTurrets(const std::string &directory, const pugi::xml_node &turrets) {
	TurretManager* tm = AppModel::getInstance().getTurretManager().get();
	pugi::xml_object_range<pugi::xml_named_node_iterator> turretNodes = turrets.children("turret");
	for (pugi::xml_named_node_iterator it = turretNodes.begin();
		it != turretNodes.end(); it++)
		tm->addTurret(directory, it->child_value());

	AppModel::getInstance().getTurretManager().release();
}

void GameManager::loadWaves(const std::string &directory, const pugi::xml_node &waves) {
    vector<string> waveList;
    pugi::xml_object_range<pugi::xml_named_node_iterator> waveNodes = waves.children("wave");
    for (pugi::xml_named_node_iterator it = waveNodes.begin();
         it != waveNodes.end(); it++)
        waveList.push_back(it->child_value());

    AppModel::getInstance().getMinionWaveManager().get()->load(directory, waveList);
    AppModel::getInstance().getMinionWaveManager().release();
}

GameManager::~GameManager() {
    this->clear();
}

int GameManager::loadItems(const string& directory, const pugi::xml_node& game, tower_defense::Map* map) {
	cout << "Loading items:\n";
	int nextItemClass = 0;
	std::map<string, int> itemTextures;

	pugi::xml_object_range<pugi::xml_named_node_iterator> items = game.child("player").child("items").children("item");

	graphics::TextureManager* textures = AppModel::getInstance().getTextures().get();

	for (pugi::xml_named_node_iterator it = items.begin(); it != items.end(); it++) {
		
		int objClass;
		string textureName = it->attribute("img").as_string();

		if (itemTextures.find(textureName) == itemTextures.end()) {
			cout << "Item texture: "<< directory + ITEM_TEXTURES_LOCATION + textureName << endl;
			textures->add(graphics::TextureManager::ITEM, objClass = nextItemClass++,
				directory + ITEM_TEXTURES_LOCATION + textureName);
			itemTextures[textureName] = objClass;
		}
		else objClass = itemTextures[textureName];
		cout << "adding to map: ";
		map->addItem(new Item(randPoint(), 0, it->attribute("size").as_double(), objClass));
		cout << "done!\n";
	}
	cout << "finished with items";

	AppModel::getInstance().getTextures().release();

	cout << '.' << endl;

	return nextItemClass;
}

inline tower_defense::Point GameManager::randPoint() const {
	return{ (mapSize - playerAreaSize) * 0.5 + (rand() % (100 * playerAreaSize)) * 0.01,
		(mapSize - playerAreaSize) * 0.5 + (rand() % (100 * playerAreaSize)) * 0.01 };
}