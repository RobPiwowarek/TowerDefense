#include "GameDisplayer.h"
#include "../logic/Game.h"
#include "../logic/Map.h"
#include "../threading/AppModel.h"
#include "../data/GameManager.h"
#include "../data/MinionManager.h"

#include <cmath>

using namespace std;
using namespace sf;
using namespace graphics;
using namespace tower_defense;
using namespace data;

void GameDisplayer::refresh(RenderWindow& window) {
	Game* g = AppModel::getInstance().getGame().get();
	window.draw(this->baseBackground);

	this->drawMapAndMinions(window, g);
	
	//TurretManager* tm = AppModel::getInstance().

	for (set<Turret*>::const_iterator it = g->getMap().getTurrets().cbegin(); it != g->getMap().getTurrets().cend(); it++)
		if (onScreen(window, **it));
			//display TODO


	AppModel::getInstance().getGame().release();
}

void GameDisplayer::setPointsPerUnit(int ppu) {
	this->pointsPerUnit = ppu < MIN_PPU ? MIN_PPU : ppu > MAX_PPU ? MAX_PPU : ppu;
}

int GameDisplayer::getPointsPerUnit() const {
	return this->pointsPerUnit;
}

void GameDisplayer::moveScreen(const Point& dp) {
	this->curPosition += dp;

	checkCurPosition();
}

void GameDisplayer::setScreenPos(const tower_defense::Point& p) {
	this->curPosition.setPoint(p);

	checkCurPosition();
}

void GameDisplayer::drawMapAndMinions(RenderWindow& window, Game* g) {
	GameManager* gm = AppModel::getInstance().getGameManager().get();
	MinionManager* mm = AppModel::getInstance().getMinionManager().get();

	int x_beginFrom, y_beginFrom, x_goTo, y_goTo;

	Point beginFrom = screenToGame(window, Vector2f(0, 0));
	Point goTo = screenToGame(window, Vector2f(window.getSize()));

	x_beginFrom = floor(beginFrom.getX());
	y_beginFrom = floor(beginFrom.getY());
	x_goTo = ceil(goTo.getX());
	y_goTo = ceil(goTo.getY());

	if (x_beginFrom < 0) x_beginFrom = 0;
	if (y_beginFrom < 0) y_beginFrom = 0;
	if (x_goTo > this->gameMapSize.getX()) x_goTo = this->gameMapSize.getX();
	if (y_goTo > this->gameMapSize.getY()) y_goTo = this->gameMapSize.getY();


	for (int i = x_beginFrom; i < x_goTo; i++)
		for (int j = y_beginFrom; j < y_goTo; j++) {
			this->display(window, gm->getMapTexture(i, j), Point(1, 1), Point(i + 0.5, j + 0.5));
			this->drawMinions(window, g->getMap().getGrid().getElement({ (double)i, (double)j }), mm);
		}

	AppModel::getInstance().getMinionManager().release();
	AppModel::getInstance().getGameManager().release();
}

void GameDisplayer::drawTurrets(sf::RenderWindow& window, tower_defense::Game* g) {
	//TODO
}
void GameDisplayer::drawMinions(sf::RenderWindow& window, tower_defense::GridElement* g, data::MinionManager* mManager) {
	for (set<Minion*>::const_iterator it = g->getMinions().cbegin(); it != g->getMinions().cend(); it++)
		display(
		window, 
		mManager->getTexture((*it)->getObjClass()),
		{ (*it)->getSize(), (*it)->getSize() },
		(*it)->getLocation());

}

bool GameDisplayer::onScreen(RenderWindow& window, const Entity &e) {
	return (e.getLocation().getX() + e.getSize() > this->curPosition.getX() - window.getSize().x / this->pointsPerUnit / 2 &&
		e.getLocation().getX() - e.getSize() < this->curPosition.getX() + window.getSize().x / this->pointsPerUnit / 2) ||
		(e.getLocation().getY() + e.getSize() > this->curPosition.getY() + window.getSize().y / this->pointsPerUnit / 2 &&
		e.getLocation().getY() - e.getSize() < this->curPosition.getY() + window.getSize().y / this->pointsPerUnit / 2);
}

GameDisplayer::GameDisplayer(const Point& startingLocation)
	: curPosition(startingLocation) {
	Map& m = AppModel::getInstance().getGame().get()->getMap();
	this->gameMapSize.setX(m.getWidth());
	this->gameMapSize.setY(m.getHeight());
	AppModel::getInstance().getGame().release();

	baseBackground.setSize(Vector2f(2000, 2000));
	baseBackground.setFillColor(Color::Black);
}

void GameDisplayer::checkCurPosition() {
	if (this->curPosition.getX() < 0)
		this->curPosition.setX(0);
	else if (this->curPosition.getX() > this->gameMapSize.getX())
		this->curPosition.setX(this->gameMapSize.getX());
	if (this->curPosition.getY() < 0)
		this->curPosition.setY(0);
	else if (this->curPosition.getY() > this->gameMapSize.getY())
		this->curPosition.setY(this->gameMapSize.getY());
}


Vector2f GameDisplayer::gameToScreen(const RenderWindow& window, const Point& inGame) const {
	return Vector2f((inGame.getX() - this->curPosition.getX()) * this->pointsPerUnit + window.getSize().x / 2,
		(inGame.getY() - this->curPosition.getY()) * this->pointsPerUnit + window.getSize().y / 2);
}

Point GameDisplayer::screenToGame(const RenderWindow& window, const Vector2f& onScreen) const {
	return Point((onScreen.x - window.getSize().x / 2) / this->pointsPerUnit + this->curPosition.getX(),
		(onScreen.y - window.getSize().y / 2) / this->pointsPerUnit + this->curPosition.getY());
}

void GameDisplayer::display(sf::RenderWindow& window, const sf::Texture& texture, const tower_defense::Point& size,
	const tower_defense::Point& position) {
	Sprite s(texture);
	s.setPosition(gameToScreen(window, position - size / 2));
	s.setScale((double)this->pointsPerUnit / size.getX() / texture.getSize().x,
		(double)this->pointsPerUnit / size.getY() / texture.getSize().y);

	window.draw(s);
}