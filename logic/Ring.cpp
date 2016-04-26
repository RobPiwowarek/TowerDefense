#include "Ring.h"

tower_defense::Ring::Ring(const int damage, const double velocity,
                          const int lifeTime, const int fireClass)
        : WeaponFire(damage, 0, lifeTime, ring, fireClass) {
    this->velocity = velocity;
}

tower_defense::Ring::Ring(const Ring &base, const double angleModifier)
        : WeaponFire(base, angleModifier) {
    this->velocity = base.velocity;
}

tower_defense::Ring::Ring(const Ring &base, const Point &location, const double angle)
        : WeaponFire(base, location, angle) {
    this->velocity = base.velocity;
}

double tower_defense::Ring::getVelocity() const {
    return this->velocity;
}

bool tower_defense::Ring::refresh(Grid& g) {
	return false; //TODO
}

bool tower_defense::Ring::hits(Minion* m) {
	return false; //TODO
}