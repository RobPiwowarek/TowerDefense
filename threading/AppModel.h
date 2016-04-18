#ifndef APP_MODEL_H
#define APP_MODEL_H

#include <mutex>
#include "ResourceManager.h"

class Refresher;


namespace tower_defense {
	class Game;
}
namespace graphics {
	class TextureManager;
}
namespace data {
	class MinionManager;
	class GameManager;
}

/*
 * Singleton class
 */

class AppModel {
public:
	// returns the instance
	static AppModel& getInstance();

	// returns the game if was initialized
	ResourceManager<tower_defense::Game>& getGame();
	//returns the refresher if was initialized
	ResourceManager<Refresher>& getRefresher();
	//returns the texture manager
	ResourceManager<graphics::TextureManager>& getTextures();
	//returns the minion manager
	ResourceManager<data::MinionManager>& getMinionManager();
	//returns the game manager
	ResourceManager<data::GameManager>& getGameManager();

	//creates the game and refresher
	//does not runs the refresher
	void createGame(std::string name);
	//closes the game
	void closeGame();

	~AppModel();
private:

	ResourceManager<tower_defense::Game>* game;
	ResourceManager<Refresher>* refresher;
	ResourceManager<graphics::TextureManager>* textureManager;
	ResourceManager<data::MinionManager>* minionManager;
	ResourceManager<data::GameManager>* gameManager;

	AppModel();

	AppModel& operator=(const AppModel& a) {

	}
};

#endif
