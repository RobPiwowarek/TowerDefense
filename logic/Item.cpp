#include "Item.h"
#include <iostream>
//TODO:
tower_defense::Item::Item(const tower_defense::Point &location, const double angle, const double size,
                          const int itemClass) : Entity(location, angle, size, itemClass) {


}

bool tower_defense::Item::drop(tower_defense::Point &location, tower_defense::Grid& grid) {

	if (grid.getElement(location)->hasItem()) return false; // cannot drop on another item.

    this->setLocation(location);
    this->holdingMinion = nullptr;

    this->held = false;
	return true;
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
	minion->setTargetPriority(tower_defense::Minion::Escape);
	std::cout << "ITEM PICKEDUP " << minion->getTargetPriority() << std::endl;
    grid.getElement(this->location)->setItem(nullptr);

    this->held = true;
    return true;
}

int tower_defense::Item::getLife() const {
    return this->playerLife;
}