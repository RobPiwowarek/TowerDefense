#include "Label.h"
#include "../threading/AppModel.h"

using namespace std;
using namespace sf;
using namespace graphics;

Label::Label(const Vector2f& size, const Vector2f&  location, const Texture* background) {
	this->background.setTexture(background);
	this->background.setSize(Vector2f(background->getSize()));
	this->setSize(size);
	this->setLocation(location);
}
Label::Label(const Vector2f&  size, const Vector2f&  location, const Texture* background, const Texture* icon)
	: Label(size, location, background) {
	this->icon = icon;
}
Label::Label(const Vector2f&  size, const Vector2f&  location, const Texture* background, const string& descr)
	: Label(size, location, background) {
	this->descr = descr;
}
Label::Label(const Vector2f&  size, const Vector2f&  location, const Texture* background, const Texture* icon, const string& descr)
	: Label(size, location, background) {
	this->icon = icon;
	this->descr = descr;
}


Vector2f& Label::getSize() {
	return this->size;
}
void Label::setSize(const Vector2f& size) {
	this->size = size;
	this->background.setScale(size.x / this->background.getTexture()->getSize().x,
		size.y / this->background.getTexture()->getSize().y);
}
Vector2f& Label::getLocation() {
	return this->location;
}
void Label::setLocation(const Vector2f& location) {
	this->location = location;
	this->background.setPosition(location);
}

void Label::setForeColor(const Color &c) {
	this->foreColor = c;
}
Color& Label::getForeColor() {
	return this->foreColor;
}

void Label::display(sf::RenderWindow& window, std::string text) {
	sf::Text label(descr + text, *AppModel::getInstance().getFont(), this->fontSize);

	window.draw(this->background);
	if (this->icon != nullptr) {
		sf::RectangleShape iconShape;
		iconShape.setSize(Vector2f(this->icon->getSize()));
		float iconScale = min(this->size.x / this->icon->getSize().x, this->size.y / this->icon->getSize().y);
		iconShape.setScale(iconScale, iconScale);
		iconShape.setPosition(this->location);
		window.draw(iconShape);
		label.setPosition(Vector2f(iconShape.getSize().x + this->location.x, this->location.y) + this->margin);
	}
	else 
		label.setPosition(this->location + this->margin);

	label.setColor(this->foreColor);

	window.draw(label);
}


void Label::setFontSize(int size) {
	this->fontSize = size;
}
int Label::getFontSize() {
	return this->fontSize;
}

const Vector2f& Label::getMargin() const {
	return this->margin;
}
void Label::setMargin(const Vector2f& margin) {
	this->margin = margin;
}