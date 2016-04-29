#ifndef GAME_CONTENT_H
#define GAME_CONTENT_H

#include "../include/SFML/Graphics.hpp"
#include "GameDisplayer.h"
#include "Label.h"
#include "../logic/Point.h"

namespace graphics {
	class GameContent {
	public:
		GameContent();
		~GameContent();
		void display(sf::RenderWindow& w);

		void manageEvent(sf::Event& e, sf::RenderWindow& w);
	private:
		void manageEvent_KeyPressed(sf::Event& e, sf::RenderWindow& w);

		GameDisplayer* displayer;
		Label* money;

	};
}

#endif