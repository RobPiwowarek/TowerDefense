#include "GameDisplayer.h"
#include "../logic/Game.h"
#include "../logic/Map.h"
#include "../threading/AppModel.h"
#include "../data/GameManager.h"
#include "../data/MinionManager.h"
#include "../data/TurretManager.h"

#include <cmath>

#define PI 3.1415

using namespace std;
using namespace sf;
using namespace graphics;
using namespace tower_defense;
using namespace data;

#include <iostream>

#define DIST_TEST
#ifdef DIST_TEST

RenderTexture* getMapTexture(int i, int j, Game* g) {
#define DIST getDistToTarget
	static sf::RenderTexture** t = nullptr;
	if (t == nullptr) {
		t = new RenderTexture*[256];
		for (int k = 0; k < 256; k++) {
			cout << "k" << k << endl;
			t[k] = new RenderTexture();
			t[k]->create(1, 1);
			sf::RectangleShape r({ 1, 1 });
			r.setFillColor(Color(0, 0, k));
			t[k]->draw(r);
		}

	}

	int blue = g->getMap().getGrid().getElement(Point(i, j))->DIST();
	if (blue < 0) blue = 0;
	if (blue > 255) blue = 255;
	return t[255-blue];
}

#endif

void GameDisplayer::refresh(RenderWindow& window) {
	Game* g = AppModel::getInstance().getGame().get();
	window.draw(this->baseBackground);

	this->drawMapAndMinions(window, g);
	
	if (this->selectedTurretBase != nullptr){
		this->drawBuildingTurret(window, g);
	}

	TurretManager* tm = AppModel::getInstance().getTurretManager().get();

	for (set<Turret*>::const_iterator it = g->getMap().getTurrets().cbegin(); it != g->getMap().getTurrets().cend(); it++)
		if (onScreen(window, **it))
			display(window, tm->getTexture((*it)->getObjClass()),
			{ (*it)->getSize(), (*it)->getSize() }, (*it)->getLocation(), (*it)->getAngle());

	AppModel::getInstance().getTurretManager().release();

	GameManager* gm = AppModel::getInstance().getGameManager().get();

	for (set<Item*>::const_iterator it = g->getMap().getItems().cbegin(); it != g->getMap().getItems().cend(); it++)
		if (onScreen(window, **it))
			display(window, gm->getItemTexture((*it)->getObjClass()), { (*it)->getSize(), (*it)->getSize() }, (*it)->getLocation());

	AppModel::getInstance().getGameManager().release();
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
		for (int j = y_beginFrom; j < y_goTo; j++)
			this->display(window,
#ifndef DISP_TEST
			gm->getMapTexture(i, j)
#else
			getMapTexture(i, j, g)->getTexture()
#endif		
			, Point(1, 1), Point(i + 0.5, j + 0.5));
	for (int i = x_beginFrom; i < x_goTo; i++)
		for (int j = y_beginFrom; j < y_goTo; j++)
			this->drawMinions(window, g->getMap().getGrid().getElement({ (double)i, (double)j }), mm);

	AppModel::getInstance().getMinionManager().release();
	AppModel::getInstance().getGameManager().release();
}

void GameDisplayer::drawBuildingTurret(RenderWindow& window, Game* g) {
	Point loc = getSelecetedTurretsLocation(window);

	sf::Texture texture;
	
	if (g->getMap().canPlaceTurret(loc, *this->selectedTurretBase)){
		texture = *AppModel::getInstance().getCanPlaceTurretBackground();
	}
	else {
		texture = *AppModel::getInstance().getCantPlaceTurretBackground();
	}
	this->display(window, texture, { this->selectedTurretBase->getSize(), this->selectedTurretBase->getSize() }, loc);

}
void GameDisplayer::drawTurrets(sf::RenderWindow& window, tower_defense::Game* g) {
	//TODO
}
void GameDisplayer::drawMinions(sf::RenderWindow& window, tower_defense::GridElement* g, data::MinionManager* mManager) {
	for (set<Minion*>::const_iterator it = g->getMinions().cbegin(); it != g->getMinions().cend(); it++)
		display( window, 
		mManager->getTexture((*it)->getObjClass()),
		{ (*it)->getSize(), (*it)->getSize() },
		(*it)->getLocation(), (*it)->getAngle());
}

bool GameDisplayer::onScreen(RenderWindow& window, const Entity &e) {
	return (e.getLocation().getX() + e.getSize() > this->curPosition.getX() - window.getSize().x / this->pointsPerUnit / 2 &&
		e.getLocation().getX() - e.getSize() < this->curPosition.getX() + window.getSize().x / this->pointsPerUnit / 2) &&
		(e.getLocation().getY() + e.getSize() > this->curPosition.getY() - window.getSize().y / this->pointsPerUnit / 2 &&
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
	const tower_defense::Point& position, double angle) {
	Sprite s(texture);
	Vector2f location = gameToScreen(window, position);

	s.setOrigin(Vector2f(s.getLocalBounds().height * 0.5, s.getLocalBounds().width * 0.5));
	s.setScale(((double)this->pointsPerUnit * size.getX()) / texture.getSize().x,
		((double)this->pointsPerUnit * size.getY()) / texture.getSize().y);
	s.setPosition(location);
	s.setRotation(angle * 180 / PI);

	window.draw(s);
}

void GameDisplayer::setBuildingTurret(const Turret* t) {
	this->selectedTurretBase = t;
}

#include <iostream>

#define P(P) cout << "(" << P.getX() << ", "<< P.getY() << ")" << endl

Point GameDisplayer::getSelecetedTurretsLocation(RenderWindow& w) {
	Point location = screenToGame(w, Vector2f(Mouse::getPosition() - w.getPosition()));
	P(location);
	if ((int)this->selectedTurretBase->getSize() % 2 == 0) location += Point(0.5, 0.5);
	P(location);
	location.setX(floor(location.getX()));
	location.setY(floor(location.getY()));
	P(location);
	if ((int)this->selectedTurretBase->getSize() % 2 == 1) location += Point(0.5, 0.5);
	P(location);

	return location;
}