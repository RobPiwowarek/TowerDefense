#ifndef GAME_DISPLAYER_H
#define GAME_DISPLAYER_H

namespace graphics {
	class GameDisplayer;
}

#include "../include/SFML/Graphics.hpp"
#include "../logic/Entity.h"
#include "../logic/Point.h"
#include "../logic/Game.h"
#include "../data/MinionManager.h"

namespace graphics {
	class GameDisplayer {
	public:
		static const int MIN_PPU = 10;
		static const int MAX_PPU = 600;

		// refreshes given window
		void refresh(graphics::GameWindow& window);
		// sets current points per unit,
		// maintaing the current centre of the screen
		void setPointsPerUnit(int ppu);
		// returns current points per unit
		int getPointsPerUnit() const;
		// moves screen by dp (in game's units)
		void moveScreen(const tower_defense::Point& dp);
		// sets screen's position as p (in game's units)
		void setScreenPos(const tower_defense::Point& p);
		//sets turret that is prepared to be build
		void setBuildingTurret(const tower_defense::Turret* t);

		sf::Vector2f gameToScreen(const graphics::GameWindow& window, const tower_defense::Point& inGame) const;
		tower_defense::Point screenToGame(const graphics::GameWindow& window, const sf::Vector2f& onScreen) const;

		tower_defense::Point getSelecetedTurretsLocation(graphics::GameWindow& w);

		GameDisplayer(const tower_defense::Point& startingLocation);
	private:
		void drawBuildingTurret(graphics::GameWindow& window, tower_defense::Game* g);
		void drawTurrets(graphics::GameWindow& window, tower_defense::Game* g);
		void drawMinions(graphics::GameWindow& window, tower_defense::GridElement* g, data::MinionManager* mManager);
		void drawMapAndMinions(graphics::GameWindow& window, tower_defense::Game* g);

		bool onScreen(graphics::GameWindow& window, const tower_defense::Entity &e);
		void checkCurPosition();

		sf::RectangleShape baseBackground;
		int pointsPerUnit = 10;
		tower_defense::Point curPosition; //in game's units
		tower_defense::Point gameMapSize;
		const tower_defense::Turret* selectedTurretBase = nullptr;


		void display(graphics::GameWindow& window, const sf::Texture& texture,
			const tower_defense::Point& size, const tower_defense::Point& position, double angle = 0);
	};
}

#endif