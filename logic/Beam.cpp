#include "Beam.h"

tower_defense::Beam::Beam(const int damage, const double maxSize, const int fireClass, const bool hitOnlyFirst, const double width)
        : WeaponFire(damage, maxSize, 1, beam, fireClass) {
    this->hitOnlyFirst = hitOnlyFirst;
	this->width = width;
}

tower_defense::Beam::Beam(const Beam &base, const Point &location, const double angle, const double angleModifier)
	: WeaponFire(base, location, angle, angleModifier) {
    this->hitOnlyFirst = base.hitOnlyFirst;
	this->width = base.width;
}

bool tower_defense::Beam::isHitOnlyFirst() const {
    return this->hitOnlyFirst;
}

bool tower_defense::Beam::refresh(Grid& g) {
	this->updateEndLocation();

	for (tower_defense::GridElement* element : g.getElementsInLine(this->location, this->endLocation, this->width/2)){
		for (tower_defense::Minion* minion : element->getMinions()){
			if (this->checkCollision(minion)){
				minion->takeDamage(this->damage);
			}
		}
	}

	this->toRemove = true;
	return false; //TODO
}

double tower_defense::Beam::getWidth() const{
	return this->width;
}

void tower_defense::Beam::updateEndLocation(){
	endLocation = { this->location.getX() + this->size*cos(this->angle), this->location.getY() + this->size*sin(this->angle) };
}

tower_defense::Point tower_defense::Beam::getEndLocation() const{
	return this->endLocation;
}

void tower_defense::Beam::setWidth(const double width){
	this->width = width;
}

void tower_defense::Beam::setEndLocation(const Point& p){
	this->endLocation = p;
}

void tower_defense::Beam::setEndLocation(const int x, const int y){
	this->endLocation = { x, y };
}

void tower_defense::Beam::setEndLocation(const double x, const double y){
	this->endLocation = { x, y };
}


bool tower_defense::Beam::hits(Minion* m) {
	return false; //TODO
}

bool tower_defense::Beam::checkCollision(tower_defense::Minion * minion){

	const double a = (this->location.getY() - this->endLocation.getY()) / (this->location.getX() - this->endLocation.getX());
	const double b = a*(-this->location.getX()) + this->location.getY();

	// y = ax + b => y - ax - b = 0

	double d = minion->getSqDistanceFromLine(a, 1, b);

	if (d <= this->width / 2) return true;

	return false; //TODO
}