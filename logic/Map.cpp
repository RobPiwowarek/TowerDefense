#include "Map.h"

tower_defense::Map::Map(const int width, const int height) {
    this->grid = new Grid(width, height, *this);
}

tower_defense::Map::~Map() {
    delete this->grid;
    for (std::set<Minion *>::iterator it = minions.begin(); it != minions.end(); it++) {
        delete *it;
    }
    for (std::set<Turret *>::iterator it = turrets.begin(); it != turrets.end(); it++) {
        delete *it;
    }
    for (std::set<WeaponFire *>::iterator it = weaponFires.begin(); it != weaponFires.end(); it++) {
        delete *it;
    }
}

std::set<tower_defense::Minion *> tower_defense::Map::getMinionsNearMinion(tower_defense::Minion * minion, double radius){
	std::set<tower_defense::Minion*> minionsNearMinion;

	for (tower_defense::Minion* m : this->minions){
		if (m == minion) continue; // exclude targeted minion

		if (m->getSqDistance(minion) <= radius*radius) minionsNearMinion.insert(m);
	}

	return minionsNearMinion;
}


std::set<tower_defense::Minion *> tower_defense::Map::getMinionsNearPoint(const tower_defense::Point & point, double radius){
	std::set<tower_defense::Minion*> minionsNearPoint;

	for (tower_defense::Minion* m : this->minions){
		if (m->getLocation().getSquareDistance(point) <= radius*radius) minionsNearPoint.insert(m);
	}

	return minionsNearPoint;
}
#include<iostream>
void tower_defense::Map::refresh(Game &game) {
    // TODO: EVERYTHING

	std::set<tower_defense::Minion*> toRemove;

    for (std::set<tower_defense::Minion*>::iterator it = this->minions.begin(); it != this->minions.end(); ++it){
		GridElement *next = nullptr, *prev = grid->getElement((*it)->getLocation());

        (*it)->refresh(*this->grid, game);

		next = grid->getElement((*it)->getLocation());

		if ((*it)->getHealth() <= 0) toRemove.insert(*it);

		if (next != prev) {
			if (prev != nullptr)	prev->removeMinion(*it);
			if (next != nullptr)	next->addMinion(*it);
			else					toRemove.insert(*it);
		}
    }
	for (tower_defense::Minion* m : toRemove) {
		std::cout << "Removing " << m << "... ";
		this->removeMinion(game, m);
		std::cout << "Destroying... ";
		delete m;
		std::cout << "Done\n";
	}

    for (std::set<tower_defense::WeaponFire*>::iterator it = this->weaponFires.begin(); it != this->weaponFires.end(); ++it){
        (*it)->refresh(*this->grid);
    }
}
#include <iostream>
bool tower_defense::Map::canPlaceTurret(const tower_defense::Point & point, const tower_defense::Turret & turret) {
	std::cout << "cPT";
	for (int i = 0; i < turret.getSize(); i++){
		for (int j = 0; j < turret.getSize(); j++){
			std::cout << "(" << i << "," << j <<")";
			tower_defense::Point temp = point - (Point(turret.getSize(), turret.getSize()) / 2) + Point(i, j);
			std::cout << "=(" << temp.getX() << "," << temp.getY() << ")\n";
			tower_defense::GridElement *tempElement = this->grid->getElement(temp);


			if (tempElement == nullptr) return false;

			if (tempElement->hasItem() || tempElement->hasTurret() || !tempElement->getMinions().empty()){
				return false;
			}
		}
	}

	return true;
}

double tower_defense::Map::getWidth() const {
    return this->grid->getWidth();
}

double tower_defense::Map::getHeight() const {
    return this->grid->getHeight();
}

void tower_defense::Map::addMinion(Minion *m) {
	this->minions.insert(m);
	this->grid->getElement(m->getLocation())->addMinion(m);
}

void tower_defense::Map::removeMinion(Game& game, Minion* m) {
	GridElement* g = grid->getElement(m->getLocation());
	if (g != nullptr) {
		g->removeMinion(m);
		if (m->hasItem()) {
			this->items.erase(m->getItem());
			delete m->getItem();
			game.getPlayer().setNItems(game.getPlayer().getNItems() - 1);
		}
	}

	

	this->minions.erase(m);
}

void tower_defense::Map::addItem(Item *i) {
	this->items.insert(i);
	this->grid->getElement(i->getLocation())->setItem(i);
	this->grid->calculateDistance(Grid::Item);
}

void tower_defense::Map::addTurret(Turret *t, Point p) {
    // TODO (Grid)
	this->grid->calculateDistance(Grid::Turret);
	this->grid->calculateDistance(Grid::Item);
}

std::set<tower_defense::Item *> &tower_defense::Map::getItems() {
    return this->items;
}

std::set<tower_defense::Minion *> &tower_defense::Map::getMinions() {
    return this->minions;
}

std::set<tower_defense::Turret *> &tower_defense::Map::getTurrets() {
    return this->turrets;
}

std::set<tower_defense::WeaponFire *> &tower_defense::Map::getWeaponFires() {
    return this->weaponFires;
}

tower_defense::Grid& tower_defense::Map::getGrid() {
	return *this->grid;
}

bool tower_defense::Map::outOfMap(const tower_defense::Point& p)const {
	return p.getX() < 0 || p.getY() < 0 || p.getX() >= this->getWidth() || p.getY() >= this->getHeight();
}