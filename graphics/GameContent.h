#ifndef GAME_CONTENT_H
#define GAME_CONTENT_H

#include "../include/SFML/Graphics.hpp"
#include "GameDisplayer.h"
#include "Label.h"
#include "../logic/Point.h"

namespace graphics {
	class GameContent {
		const static int MONEY_LABEL_WIDTH = 100;
		const static int MONEY_LABEL_HEIGHT = 25;
		const static int MONEY_LABEL_X = 10;
		const static int MONEY_LABEL_Y = 10;
		const static int MONEY_LABEL_FONT_SIZE = 20;

		const static int TURRET_LABEL_WIDTH = 150;
		const static int TURRET_LABEL_HEIGHT = 20;
		const static int TURRET_LABELS_X = 450;
		const static int TURRET_LABELS_Y = 50;
		const static int TURRET_LABELS_Y_DIFF = 25;
		const static int TURRET_LABEL_FONT_SIZE = 15;

		const static unsigned int WINDOW_HEIGHT = 600;
		const static unsigned int WINDOW_WIDTH = 600;

		const static int FINISHED_LABEL_WIDTH = 60;
		const static int FINISHED_LABEL_HEIGHT = 25;
		const static int FINISHED_LABEL_X = 270;
		const static int FINISHED_LABEL_Y = 400;
		const static int FINISHED_LABEL_FONT_SIZE = 20;
	public:
		GameContent(sf::RenderWindow& w);
		~GameContent();
		void refresh(sf::RenderWindow& w);

	private:
		void createTurretList();

		void checkKeys(sf::RenderWindow& w);

		GameDisplayer* displayer;

		// game ui
		void displayUI_game(sf::RenderWindow& w);

		Label* money;
		std::vector <std::pair<int, std::pair<std::string, int> > > turretList;
		Label** turretLabels;
		int turretN = 0;

		// game finished ui
		void displayUI_finished(sf::RenderWindow& w);

		Label* confirmLabel;


		bool keys[sf::Keyboard::KeyCount];

		void manageEvent(sf::Event& e, sf::RenderWindow& w);
		void manageEvent_mousePress(sf::Event& e, sf::RenderWindow& w);
		void manageEvent_mousePress_gameGoing(sf::Event& e, sf::RenderWindow& w);
		void manageEvent_mousePress_gameFinished(sf::Event& e, sf::RenderWindow& w);

		int selectedTurret = -1;


		sf::Sprite& getDefeatScreen(sf::RenderWindow& w);
		sf::Sprite& getVictoryScreen(sf::RenderWindow& w);

		//DEBUG:
		Label* debugL;
	};
}

#endif