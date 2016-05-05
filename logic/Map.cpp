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

void tower_defense::Map::refresh(Game &game) {
    // TODO: EVERYTHING

    for (std::set<tower_defense::Minion*>::iterator it = this->grid->getMinions().begin(); it != this->grid->getMinions().end(); ++it){
        (*it)->refresh(*this->grid, game);
    }

    for (std::set<tower_defense::WeaponFire*>::iterator it = this->weaponFires.begin(); it != this->weaponFires.end(); ++it){
        (*it)->refresh(*this->grid);
    }
}

bool tower_defense::Map::canPlaceTurret(const tower_defense::Point & point, const tower_defense::Turret & turret){
	for (int i = 0; i < turret.getSize(); i++){
		for (int j = 0; j < turret.getSize(); j++){
			tower_defense::Point *temp = new Point(turret.getLocation().getX() + j, turret.getLocation().getY() + i);
			tower_defense::GridElement *tempElement = this->grid->getElement(*temp);

			delete temp;

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
    // TODO (Grid)
}

void tower_defense::Map::addItem(Item *i) {
    // TODO (Grid)
}

void tower_defense::Map::addTurret(Turret *t, Point p) {
    // TODO (Grid)
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