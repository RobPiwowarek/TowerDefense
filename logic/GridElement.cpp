#include "GridElement.h"

tower_defense::GridElement::GridElement(const Point& location) {
	this->location = location;

	this->distToTarget = 0;
	this->distToTurret = 0;
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

std::set<tower_defense::Minion*>& tower_defense::GridElement::getMinions() {
	return this->minions;
}

tower_defense::Point tower_defense::GridElement::getLocation() const {
	return this->location;
}