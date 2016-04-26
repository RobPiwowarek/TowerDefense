#include "GridElement.h"

tower_defense::GridElement::GridElement(const Point &location, Grid &g) : grid(g) {
    this->location = location;

    this->distToTarget = 0;
    this->distToTurret = 0;
}

tower_defense::Turret *tower_defense::GridElement::getTurret() {
    return this->turret;
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