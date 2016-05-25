#ifndef LOADING_CONTENT_H
#define LOADING_CONTENT_H

namespace graphics {
	class LoadingContent;
}

#include "Content.h"
#include "GameWindow.h"
#include "Label.h"
#include "../include/SFML/Graphics.hpp"

namespace graphics {
	class LoadingContent : Content {
		const float TEXT_X = 260;
		const float TEXT_Y = 280;
		const float TEXT_WIDTH = 80;
		const float TEXT_HEIGHT = 40;
		const int FONT_SIZE = 30;
	public:
		LoadingContent(GameWindow* w);
		~LoadingContent();
		void display();
		void manageEvent(sf::Event& e) {

		}
	private:
		graphics::Label* text = nullptr;
	};
}

#endif