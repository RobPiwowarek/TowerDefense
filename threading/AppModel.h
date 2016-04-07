#ifndef APP_MODEL_H
#define APP_MODEL_H

#include <mutex>

class Refresher;
template<class T> class ResourceManager;

namespace tower_defense {
	class Game;
}
namespace graphics {
	class TextureManager;
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

	//creates the game and refresher
	//does not runs the refresher
	void createGame(std::string name);
	//closes the game
	void closeGame();

	~AppModel();
private:
	static std::mutex instanceLocker;

	ResourceManager<tower_defense::Game>* game;
	ResourceManager<Refresher>* refresher;
	ResourceManager<graphics::TextureManager>* textureManager;

	AppModel();

	AppModel& operator=(const AppModel& a) {

	}
};

#endif
