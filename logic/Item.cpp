#include "Item.h"

//TODO:
tower_defense::Item::Item(const tower_defense::Point &location, const double angle, const double size,
                          const int itemClass) : Entity(location, angle, size, itemClass) {


}

bool tower_defense::Item::drop(tower_defense::Point &location) {

    this->setLocation(location);
    this->holdingMinion = nullptr;

    this->held = false;
}

bool tower_defense::Item::isHeld() const {
    return this->held;
}

tower_defense::Minion* tower_defense::Item::getHoldingMinion() {
    return this->holdingMinion;
}

// TODO: maybe exception check?
bool tower_defense::Item::pickUp(tower_defense::Minion* minion, tower_defense::Grid& grid) {
    if (this->held) return false;

    this->holdingMinion = minion;
    minion->setItem(this);
    grid.getElement(this->location)->setItem(nullptr);

    this->held = true;
    return true;
}

int tower_defense::Item::getLife() const {
    return this->playerLife;
}