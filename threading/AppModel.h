#ifndef APP_MODEL_H
#define APP_MODEL_H

#include <mutex>
#include <atomic>
#include "../include/SFML/Graphics.hpp"
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

    class MinionWaveManager;

    class GameManager;

	class TurretManager;

	class WeaponFireManager;
}

/*
 * Singleton class
 */

class AppModel {
	const char* FONT_LOCATION = "res/basic/arial.ttf";
	const char* LABEL_BACKGROUND = "res/basic/label.png";
	const char* PLACEHOLDER_TURRET_BACKGROUND_CAN_PLACE = "res/turrets/PLACEHOLDER_CAN_PLACE_FLAME.png";
	const char* PLACEHOLDER_TURRET_BACKGROUND_CANT_PLACE = "res/turrets/PLACEHOLDER_CANT_PLACE_FLAME.png";
	const int LABEL_BACKGORUND_OID = 0;
	const int PLACEHOLDER_TURRET_BACKGROUND_CAN_PLACE_OID = 1;
	const int PLACEHOLDER_TURRET_BACKGROUND_CANT_PLACE_OID = 2;
public:
	enum GameState {
		MainMenu,
		Loading,
		Going,
		Paused,
		Victory,
		Defeat
	};

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
	//returns the minion wave manager
	ResourceManager<data::MinionWaveManager>& getMinionWaveManager();
	//returns the turret manager
	ResourceManager<data::TurretManager>& getTurretManager();
	//returns the weapon fire manager
	ResourceManager<data::WeaponFireManager>& getWeaponFireManager();
	//returns the game manager
	ResourceManager<data::GameManager>& getGameManager();

	//returns the default font
	const sf::Font* getFont();
	//returns basic texture for the label's background
	const sf::Texture* getLabelBackground();

	//returns basic texture for placing turrets 
	const sf::Texture* getCanPlaceTurretBackground();

	//returns basic texture for placing turrets 
	const sf::Texture* getCantPlaceTurretBackground();

	//creates the game and refresher
	//does not runs the refresher
	//return true on success
	bool createGame(const std::string& xmlURI);
	//closes the game
	void closeGame();
	//pauses the game
	void pauseGame();
	//runs paused game
	void unpauseGame();
	
	void setState(GameState s);
	GameState getState();
private:
	std::atomic<GameState> state;

    ResourceManager<tower_defense::Game> *game;
    ResourceManager<Refresher> *refresher;
    ResourceManager<graphics::TextureManager> *textureManager;
    ResourceManager<data::MinionManager> *minionManager;
	ResourceManager<data::GameManager> *gameManager;
	ResourceManager<data::MinionWaveManager> *minionWaveManager;
	ResourceManager<data::TurretManager> *turretManager;
	ResourceManager<data::WeaponFireManager> *weaponFireManager;

	sf::Font* font = nullptr;

	void loadResources();


	~AppModel();
    AppModel();

    AppModel &operator=(const AppModel &a) {

    }
	AppModel(const AppModel& a) {

	}
};

#endif
