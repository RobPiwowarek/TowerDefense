#include "Content.h"
#include "Label.h"

using namespace graphics;
using namespace std;
using namespace sf;

Content::Content(GameWindow* w) {
	this->parent = w;
}

Label* Content::getLabel(sf::Vector2f location) {
	for (Label* l : this->labels) {
		if (location.x >= l->getLocation().x && location.y >= l->getLocation().y &&
			location.x <= l->getLocation().x + l->getSize().x && location.y <= l->getLocation().y + l->getSize().y)
			return l;
	}

	return nullptr;
}