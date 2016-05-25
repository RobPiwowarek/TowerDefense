#ifndef CONTENT_H
#define CONTENT_H

#include <list>

namespace grpahics {
	class Content;
}

#include "../include/SFML/Graphics.hpp"

namespace graphics {
	class GameWindow;
	class Label;

	class Content {
	public:
		Content(GameWindow* parent);
		virtual void display() = 0;
		virtual void manageEvent(sf::Event& e) = 0;
	protected:
		GameWindow* parent;

		std::list<Label*> labels;
		Label* getLabel(sf::Vector2f location);
	};
}

#endif