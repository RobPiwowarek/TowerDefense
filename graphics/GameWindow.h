#ifndef GAME_WINDOW_H
#define GAME_WINDOW_H

#include <thread>
#include <atomic>
#include <mutex>

namespace graphics {
	class GameWindow;
	class LoadingContent;
	class GameContent;
	class Content;
}

#include "../include/SFML/Graphics.hpp"
#include "TextureManager.h"
#include "LoadingContent.h"

namespace tower_defense {
	class Turret;
	class Minion;
	class WeaponFire;
	class Item;
}

namespace graphics {

	class GameWindow : public sf::RenderWindow {
		const char* FONT_LOCATION = "res/basic/arial.ttf";
		const char* LABEL_BACKGROUND = "res/basic/label.png";
		const char* VICTORY_TEXTURE = "res/basic/victory.png";
		const char* DEFEAT_TEXTURE = "res/basic/defeat.png";
		const char* PLACEHOLDER_TURRET_BACKGROUND_CAN_PLACE = "res/turrets/PLACEHOLDER_CAN_PLACE_FLAME.png";
		const char* PLACEHOLDER_TURRET_BACKGROUND_CANT_PLACE = "res/turrets/PLACEHOLDER_CANT_PLACE_FLAME.png";
		const char* MENU_BACKGROUND = "res/basic/menu.png";
		const char* EXPLOSIONS = "res/basic/expl";
		const int EXPLOSIONS_N = 6;
		const char* EXPLOSION_SUFFIX = ".png";

		const int LABEL_BACKGORUND_OID = 0;
		const int PLACEHOLDER_TURRET_BACKGROUND_CAN_PLACE_OID = 1;
		const int PLACEHOLDER_TURRET_BACKGROUND_CANT_PLACE_OID = 2;
		const int VICTORY_TEXTURE_OID = 3;
		const int DEFEAT_TEXTURE_OID = 4;
		const int MENU_BACKGROUND_OID = 5;

		const int REFRESHER_DELAY = 20;

	public:
		const static unsigned int WINDOW_HEIGHT = 600;
		const static unsigned int WINDOW_WIDTH = 600;

		GameWindow();
		~GameWindow();

		//returns texture for given entity
		const sf::Texture* getTexture(const tower_defense::Turret* const) const;
		//returns texture for given entity
		const sf::Texture* getTexture(const tower_defense::Minion* const) const;
		//returns texture for given entity
		const sf::Texture* getTexture(const tower_defense::WeaponFire* const) const;
		//returns texture for given entity
		const sf::Texture* getTexture(const tower_defense::Item* const) const;

		// returns texture for map piece at given coordinates
		const sf::Texture* getMapTexture(int x, int y) const;

		//returns the default font
		const sf::Font* getFont() const;
		//returns basic texture for the label's background
		const sf::Texture* getLabelBackground() const;

		//returns basic texture for placing turrets 
		const sf::Texture* getCanPlaceTurretBackground() const;

		//returns basic texture for placing turrets 
		const sf::Texture* getCantPlaceTurretBackground() const;

		//returns texture for defeat screen
		const sf::Texture* getDefeatTexture() const;
		//returns texture for victory screen
		const sf::Texture* getVictoryTexture() const;

		//returns texture for menu
		const sf::Texture* getMenuBackground() const;

		//returns random explosion texture
		const sf::Texture* getExplosion() const;

		//returns pointer to the texture manager (thread unsafe!)
		TextureManager* getTextureManager();

		//starts refreshing of graphics
		void start();
		//stops refreshing of graphics
		void stop();
	private:
		Content* currentContent = nullptr;
		LoadingContent* loadingContent = nullptr;
		GameContent* gameContent = nullptr;

		sf::Font* font = nullptr;

		TextureManager* tm;

		std::atomic<bool> stopFlag = false;

		void refresh();

		void loadResources();
	};
}

#endif