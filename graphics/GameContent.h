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
	public:
		GameContent(sf::RenderWindow& w);
		~GameContent();
		void display(sf::RenderWindow& w);

		void manageEvent(sf::Event& e, sf::RenderWindow& w);
	private:
		void createTurretList();

		void manageEvent_KeyPressed(sf::Event& e, sf::RenderWindow& w);

		GameDisplayer* displayer;
		Label* money;
		std::vector <std::pair<int, std::pair<std::string, int> > > turretList;
		Label** turretLabels;
		int turretN = 0;

	};
}

#endif