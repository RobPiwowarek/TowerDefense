#include "Ring.h"
#include <iostream>
tower_defense::Ring::Ring(const int damage, const double velocity, const double size,
	const int lifeTime, const int fireClass, const double innerRadius)
	: WeaponFire(damage, size, lifeTime, ring, fireClass) {
	std::cout << "{R" << size << " " << this->size << "}";
    this->velocity = velocity;
	this->innerRadius = innerRadius;
}

tower_defense::Ring::Ring(const Ring &base, const Point &location, const double angle, const double angleModifier)
	: WeaponFire(base, location, angle, angleModifier) {
    this->velocity = base.velocity;
	this->innerRadius = base.innerRadius;
}

double tower_defense::Ring::getVelocity() const {
    return this->velocity;
}

std::string tower_defense::Ring::toString() const {
	std::string info = std::string("Beam: Damage: ") + (char)this->damage + " Angle: " + (char)this->angle + " Size: " + (char)this->size
		+ " Inner Radius: " + (char)this->innerRadius  + " LifeTime: " + (char) this->lifeTime + " Velocity: " + (char) this->velocity + " Location: " 
		+ this->location.toString();

	return info;
}

void tower_defense::Ring::print() const{
	std::cout << this->toString() << std::endl;
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
	this->innerRadius += this->velocity;

	return true; //TODO
}

bool tower_defense::Ring::hits(Minion* m) {
	return false; //TODO
}

void tower_defense::Ring::setInnerRadius(const double r){
	this->innerRadius = r;
}

double tower_defense::Ring::getInnerRadius() const {
	return this->innerRadius;
}

bool tower_defense::Ring::checkCollision(tower_defense::Minion * minion) {
	if (!minion) return false;

	double d = minion->getSqDistance(this);

	if (pow(this->size / 2 + minion->getSize() / 2, 2.0f) >= d){
		return true;
	}

	return false; //TODOs
}