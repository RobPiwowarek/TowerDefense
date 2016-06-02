#ifndef APP_MODEL_H
#define APP_MODEL_H

#include <mutex>
#include <atomic>
#include "../include/SFML/Graphics.hpp"
#include "ResourceManager.h"
#include "../graphics/GameWindow.h"

class Refresher;


namespace tower_defense {
    class Game;
}
namespace data {
    class MinionManager;

    class MinionWaveManager;

    class GameManager;

	class TurretManager;

	class WeaponFireManager;
}

/*
 * Singleton class
 */


class AppModel {
public:
	enum GameState {
		MainMenu,
		Loading,
		Going,
		Paused,
		Victory,
		Defeat
	};
	
	std::string DEFAULT_GAME = "\\res\\game.xml";

	// returns the instance
	static AppModel& getInstance();

	// returns the game if was initialized
	ResourceManager<tower_defense::Game>& getGame();
	//returns the refresher if was initialized
	ResourceManager<Refresher>& getRefresher();
	//returns the minion manager
	ResourceManager<data::MinionManager>& getMinionManager();
	//returns the minion wave manager
	ResourceManager<data::MinionWaveManager>& getMinionWaveManager();
	//returns the turret manager
	ResourceManager<data::TurretManager>& getTurretManager();
	//returns the weapon fire manager
	ResourceManager<data::WeaponFireManager>& getWeaponFireManager();
	//returns the game manager
	ResourceManager<data::GameManager>& getGameManager();

	//creates the game and refresher
	//runs the refresher
	//return true on success
	bool createGame(const std::string& xmlURI);
	//creates a game from DEFAULT_GAME
	bool createGame();
	//closes the game
	void closeGame();
	//pauses the game
	void pauseGame();
	//runs paused game
	void unpauseGame();
	
	// sets given game state
	void setState(GameState s);
	// returns current game state
	GameState getState();

	// opens game window
	void runWindow();
private:
	std::atomic<GameState> state;

	graphics::GameWindow* window = nullptr;

    ResourceManager<tower_defense::Game> *game;
    ResourceManager<Refresher> *refresher;
    ResourceManager<data::MinionManager> *minionManager;
	ResourceManager<data::GameManager> *gameManager;
	ResourceManager<data::MinionWaveManager> *minionWaveManager;
	ResourceManager<data::TurretManager> *turretManager;
	ResourceManager<data::WeaponFireManager> *weaponFireManager;


	~AppModel();
    AppModel();

    AppModel &operator=(const AppModel &a) {

    }
	AppModel(const AppModel& a) {

	}
};

#endif
