#include "GameManager.h"
#include "MinionWaveManager.h"

#include "../threading/AppModel.h"
#include "../threading/ResourceManager.h"
#include "../graphics/TextureManager.h"

#include "../include/pugixml/pugixml.hpp"

#include <cstdlib>

#include <exception>



using namespace data;
using namespace tower_defense;
using namespace std;
using namespace sf;

#define POINT_OUT_OF_MAP throw exception("Exception: Given point is out of map");

#define FAILED_TO_LOAD_GAME throw exception("Exception: Failed to load game");

void GameManager::clear() {
	this->mapTextures.clear();
	//TODO
}

Game* GameManager::load(const string& path) {
	string directory = path;
	for (int i = directory.size() - 1; i >= 0; i--) {
		if (directory[i] == '/' || directory[i] == '\\') {
			directory = path.substr(0, i + 1);
			break;
		}
	}

	Map* map; Player* player;


	pugi::xml_document gameDoc;
	pugi::xml_parse_result result = gameDoc.load_file(path.c_str(), pugi::parse_full | pugi::parse_trim_pcdata, pugi::encoding_utf8);

	if (result.status != pugi::status_ok)
		FAILED_TO_LOAD_GAME

	pugi::xml_node game = gameDoc.child("game");

	map = loadMap(directory, game.child("map"));
	player = loadPlayer(directory, game.child("player"));

	loadWaves(directory, game.child("waves"));

	//TODO load items, turrets;

	return new Game(map, player);
}

const Texture& GameManager::getMapTexture(int x, int y) const {
	if (x >= this->mapSize || y >= this->mapSize || x < 0 || y < 0)
		POINT_OUT_OF_MAP

	const Texture& toRet = AppModel::getInstance().getTextures().get()->get(this->mapTextures.find(make_pair(x, y))->second);
	AppModel::getInstance().getTextures().release();

	return toRet;
}

Map* GameManager::loadMap(const string& directory, const pugi::xml_node& map) {
	graphics::TextureManager* textureManager = AppModel::getInstance().getTextures().get();

	std::map<string, unsigned int> loadedTextures;

	this->mapSize = atoi(map.child("size").child_value());

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

Player* GameManager::loadPlayer(const std::string& directory, const pugi::xml_node& player) {
	return new Player(atoi(player.child("startingMoney").child_value()));
}

void GameManager::loadWaves(const std::string& directory, const pugi::xml_node& waves) {
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