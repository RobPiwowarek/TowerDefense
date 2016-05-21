#include "Ring.h"

tower_defense::Ring::Ring(const int damage, const double velocity,
	const int lifeTime, const int fireClass)
        : WeaponFire(damage, 0, lifeTime, ring, fireClass) {
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
	tower_defense::GridElement * temp = g.getElement(this->location);

	if (!temp->getMinions().empty()){
		for (tower_defense::Minion* minion : temp->getMinions()){
			if (this->checkCollision(minion)){

				/// mozna trafione miniony gdzies zachowac i dalej z nimi cos zrobic
			}
		}
	}

	this->size += this->velocity;

	return false; //TODO
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