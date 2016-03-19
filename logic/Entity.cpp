#include "Entity.h"
#include <cmath>

tower_defense::Entity::Entity(
        const tower_defense::Point &location, const double angle, const double size, const int objClass) {
    this->location = location;
    this->angle = angle;
    this->size = size;
    this->objClass = objClass;
}

tower_defense::Entity::Entity(const Entity &e)
        : Entity(e.location, e.angle, e.size, e.objClass) {
}

double tower_defense::Entity::getSqDistance(const tower_defense::Entity *e) {
    return pow(e->getLocation().getX() - this->getLocation().getX(), 2.0f) +
           pow(e->getLocation().getY() - this->getLocation().getY(), 2.0f);
}

double tower_defense::Entity::getAngle() const {
    return this->angle;
}

void tower_defense::Entity::setAngle(double angle) {
    this->angle = angle;
}

tower_defense::Point tower_defense::Entity::getLocation() const {
    return this->location;
}

void tower_defense::Entity::setLocation(const tower_defense::Point &location) {
    this->location = location;
}

double tower_defense::Entity::getSize() const {
    return this->size;
}

int tower_defense::Entity::getObjClass() const {
    return this->objClass;
}