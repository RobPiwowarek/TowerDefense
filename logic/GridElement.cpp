#include "GridElement.h"

tower_defense::GridElement::GridElement(const Point &location, Grid &g) : grid(g) {
    this->location = location;

    this->distToTarget = 0;
    this->distToTurret = 0;
}

tower_defense::Turret *tower_defense::GridElement::getTurret() {
    return this->turret;
}

void tower_defense::GridElement::addMinion(Minion *m) {
    this->minions.insert(m);
    this->grid.addMinion(m);
}

void tower_defense::GridElement::removeMinion(Minion *m) {
    this->minions.erase(m);
}

bool tower_defense::GridElement::setTurret(Turret *t) {
    if (this->minions.empty() || this->turret != nullptr)
        return false;

    this->occupied = true;
    this->turret = t;
    return true;
}

tower_defense::GridElement *tower_defense::GridElement::getUpNeighbour() const {
    int y = this->location.getY() - 1;

    GridElement* temp = grid.getElement(Point(this->location.getX(), y));

    if (temp == nullptr) return nullptr;

    return temp;
}

tower_defense::GridElement *tower_defense::GridElement::getDownNeighbour() const {
    int y = this->location.getY() + 1;

    GridElement* temp = grid.getElement(Point(this->location.getX(), y));

    if (temp == nullptr) return nullptr;

    return temp;
}

tower_defense::GridElement *tower_defense::GridElement::getLeftNeighbour() const {
    int x = this->location.getY() - 1;

    GridElement* temp = grid.getElement(Point(x, this->location.getY()));

    if (temp == nullptr) return nullptr;

    return temp;
}

tower_defense::GridElement *tower_defense::GridElement::getRightNeighbour() const {
    int x = this->location.getY() + 1;

    GridElement* temp = grid.getElement(Point(x, this->location.getY()));

    if (temp == nullptr) return nullptr;

    return temp;
}

void tower_defense::GridElement::addMissile(tower_defense::WeaponFire* missile){
	this->missiles.insert(missile);
}

void tower_defense::GridElement::removeMissile(tower_defense::WeaponFire* missile){
	this->missiles.erase(missile);
}

std::set<tower_defense::WeaponFire*> tower_defense::GridElement::getMissiles() const{
	return this->missiles;
}

bool tower_defense::GridElement::hasItem() const{
    return this->distToTarget == 0 && this->item != nullptr;
}

bool tower_defense::GridElement::hasItem(tower_defense::Item *item) const{
    return this->item == item;
}

tower_defense::Item& tower_defense::GridElement::getItem() const { return *this->item; }

void tower_defense::GridElement::setItem(tower_defense::Item *item) { this->item = item; }

bool tower_defense::GridElement::hasTurret() const {
    return occupied;
}

int tower_defense::GridElement::getDistToTarget() const {
    return this->distToTarget;
}

void tower_defense::GridElement::setDistToTarget(const int dist) {
    this->distToTarget = dist;
}

int tower_defense::GridElement::getDistToTurret() const {
    return this->distToTurret;
}

void tower_defense::GridElement::setDistToTurret(const int dist) {
    this->distToTurret = dist;
}

std::set<tower_defense::Minion *> &tower_defense::GridElement::getMinions() {
    return this->minions;
}

tower_defense::Point tower_defense::GridElement::getLocation() const {
    return this->location;
}