#include "LoadingContent.h"

using namespace graphics;
using namespace sf;
#include <iostream>
LoadingContent::LoadingContent(GameWindow* w) : Content(w) {
	this->text = new Label({ TEXT_X, TEXT_Y }, { TEXT_WIDTH, TEXT_HEIGHT }, w->getDefeatTexture(), "Loading...");
	this->text->setForeColor(Color::White);
	this->text->setFontSize(FONT_SIZE);
}

LoadingContent::~LoadingContent() {
	delete text;
}

void LoadingContent::display() {
	RectangleShape bg({ (float)GameWindow::WINDOW_HEIGHT, (float)GameWindow::WINDOW_WIDTH });
	bg.setFillColor(Color::Black);
	this->parent->draw(bg);
	this->text->display(*this->parent, "");
}