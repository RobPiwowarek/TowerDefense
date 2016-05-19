#include "Beam.h"

tower_defense::Beam::Beam(const int damage, const double maxSize, const int fireClass, const bool hitOnlyFirst, const double width)
        : WeaponFire(damage, maxSize, 1, beam, fireClass) {
    this->hitOnlyFirst = hitOnlyFirst;
	this->width = width;
}

tower_defense::Beam::Beam(const Beam &base, const double angleModifier)
        : WeaponFire(base, angleModifier) {
    this->hitOnlyFirst = base.hitOnlyFirst;
	this->width = base.width;
}

tower_defense::Beam::Beam(const Beam &base, const Point &location, const double angle)
        : WeaponFire(base, location, angle) {
    this->hitOnlyFirst = base.hitOnlyFirst;
	this->width = base.width;
}

bool tower_defense::Beam::isHitOnlyFirst() const {
    return this->hitOnlyFirst;
}

bool tower_defense::Beam::refresh(Grid& g) {
	for (tower_defense::GridElement* element : g.getElementsInLine(this->location, this->location + this->size, this->width/2)){
		for (tower_defense::Minion* minion : element->getMinions()){
			if (this->checkCollision(minion)){
				minion->takeDamage(this->damage);
			}
		}
	}

	return false; //TODO
}

double tower_defense::Beam::getWidth() const{
	return this->width;
}

void tower_defense::Beam::setWidth(const double width){
	this->width = width;
}


bool tower_defense::Beam::hits(Minion* m) {
	return false; //TODO
}

bool tower_defense::Beam::checkCollision(tower_defense::Minion * minion){

	const double a = (this->location.getY() - this->location.getY()-this->size) / (this->location.getX() - this->location.getX()-this->size);
	const double b = a*(-this->location.getX()) + this->location.getY() + this->size;

	// y = ax + b => y - ax - b = 0

	double d = minion->getSqDistanceFromLine(a, 1, b);

	if (d <= this->width / 2) return true;

	return false; //TODO
}