#include "GridElement.h"

tower_defense::GridElement::GridElement(const Point &location, Grid &g) : grid(g) {
    this->location = location;

    this->distToTarget = -1;
    this->distToTurret = -1;
}

int tower_defense::GridElement::getDistToCorner() const{
	return this->distToCorner;
}

void tower_defense::GridElement::setDistToCorner(const int dist){
	this->distToCorner = dist;
}

int tower_defense::GridElement::getDistToEdge() const{
	return this->distToEdge;
}

void tower_defense::GridElement::setDistToEdge(const int dist){
	this->distToEdge = dist;
}

tower_defense::Turret *tower_defense::GridElement::getTurret() {
    return this->turret;
}

void tower_defense::GridElement::addMinion(Minion *m) {
    this->minions.insert(m);
}

void tower_defense::GridElement::removeMinion(Minion *m) {
    this->minions.erase(m);
}

bool tower_defense::GridElement::setTurret(Turret *t) {
	if (t != nullptr) {
		this->occupied = true;
		this->turret = t;
	}
	else {
		this->occupied = false;
		this->turret = nullptr;
	}
    return true;
}

tower_defense::GridElement *tower_defense::GridElement::getUpNeighbour() const {
    double y = this->location.getY() - 1;

    GridElement* temp = grid.getElement(Point(this->location.getX(), y));

    return temp;
}

tower_defense::GridElement *tower_defense::GridElement::getDownNeighbour() const {
    double y = this->location.getY() + 1;

    GridElement* temp = grid.getElement(Point(this->location.getX(), y));

    return temp;
}

tower_defense::GridElement *tower_defense::GridElement::getLeftNeighbour() const {
    double x = this->location.getX() - 1;

    GridElement* temp = grid.getElement(Point(x, this->location.getY()));

    return temp;
}

tower_defense::GridElement *tower_defense::GridElement::getRightNeighbour() const {
    double x = this->location.getX() + 1;

    GridElement* temp = grid.getElement(Point(x, this->location.getY()));

    return temp;
}

bool tower_defense::GridElement::hasItem() const{
    return this->items.size() != 0;
}

bool tower_defense::GridElement::hasItem(tower_defense::Item *item) const{
	for (Item* i : this->items){
		if (i == item) return true;
	}
	return false;
}

std::set<tower_defense::Item*> tower_defense::GridElement::getItems() const { return this->items; }

void tower_defense::GridElement::addItem(tower_defense::Item *item) { this->items.insert(item); }

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