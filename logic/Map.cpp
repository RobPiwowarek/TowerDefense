#include "Map.h"

tower_defense::Map::Map(const int width, const int height, Game &g):game(g) {
    this->grid = new Grid(width, height, *this);
}

tower_defense::Map::~Map() {
	delete this->grid;
	for (std::set<Minion*>::iterator it = minions.begin(); it != minions.end(); it++) {
		delete *it;
	}
	for (std::set<Turret*>::iterator it = turrets.begin(); it != turrets.end(); it++) {
		delete *it;
	}
	for (std::set<WeaponFire*>::iterator it = weaponFires.begin(); it != weaponFires.end(); it++) {
		delete *it;
	}
}

tower_defense::Grid& tower_defense::Map::getGrid() const {
	return this->*grid;
}

void tower_defense::Map::refresh(Player &p, Game& game) {
	// TODO: EVERYTHING
}

double tower_defense::Map::getWidth() const {
	return this->grid->getWidth();
}

double tower_defense::Map::getHeight() const {
	return this->grid->getHeight();
}

void tower_defense::Map::addMinion(Minion* m) {
	// TODO (Grid)
}

void tower_defense::Map::addItem(Item *i) {
    // TODO (Grid)
}

void tower_defense::Map::addTurret(Turret* t, Point p) {
	// TODO (Grid)
}

std::set<tower_defense::Item*>& tower_defense::Map::getItems() {
	return this->items;
}

std::set<tower_defense::Minion*>& tower_defense::Map::getMinions() {
	return this->minions;
}

std::set<tower_defense::Turret*>& tower_defense::Map::getTurrets() {
	return this->turrets;
}

std::set<tower_defense::WeaponFire*>& tower_defense::Map::getWeaponFires() {
	return this->weaponFires;
}
