#include "Ring.h"
#include <iostream>
tower_defense::Ring::Ring(const int damage, const double velocity,
	const int lifeTime, const int fireClass)
	: WeaponFire(damage, 0, lifeTime, ring, fireClass) {
	std::cout << "{R" << size << " " << this->size << "}";
    this->velocity = velocity;
}

tower_defense::Ring::Ring(const Ring &base, const Point &location, const double angle, const double angleModifier)
	: WeaponFire(base, location, angle, angleModifier) {
    this->velocity = base.velocity;
}

double tower_defense::Ring::getVelocity() const {
    return this->velocity;
}

bool tower_defense::Ring::refresh(Grid& g) {
	if (this->lifeTime-- == 0) {
		this->toRemove = true;
		return false;
	}
	std::set<tower_defense::GridElement*> elements;

	elements = g.getElementsInRadius(this->location, this->size);

	for (tower_defense::GridElement* element : elements){
		for (tower_defense::Minion* minion : element->getMinions()){
			if (this->checkCollision(minion)){
				minion->takeDamage(this->damage);
			}
		}
	}

	this->size += this->velocity;

	return true; //TODO
}

bool tower_defense::Ring::hits(Minion* m) {
	return false; //TODO
}

bool tower_defense::Ring::checkCollision(tower_defense::Minion * minion) {
	if (!minion) return false;

	if (pow(this->size + minion->getSize(), 2.0f) >= minion->getSqDistance(this)){
		return true;
	}

	return false; //TODOs
}