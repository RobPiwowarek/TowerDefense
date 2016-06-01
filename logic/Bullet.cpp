#include "Bullet.h"
#include <iostream>


tower_defense::Bullet::Bullet(const int damage, const double size, const bool hitOnlyFirst, const double splash,
                              const double velocity, const int lifeTime, const int fireClass)
							  : WeaponFire(damage, size, lifeTime, bullet, fireClass) {
    this->hitOnlyFirst = hitOnlyFirst;
    this->splash = splash;
    this->velocity = velocity;
}

tower_defense::Bullet::Bullet(const Bullet &base, const Point &location, const double angle, const double angleModifier)
        : WeaponFire(base, location, angle, angleModifier) {
    this->hitOnlyFirst = base.hitOnlyFirst;
    this->splash = base.splash;
    this->velocity = base.velocity;
}


bool tower_defense::Bullet::isHitOnlyFirst() const {
    return this->hitOnlyFirst;
}

double tower_defense::Bullet::getSplash() const {
    return this->splash;
}

double tower_defense::Bullet::getVelocity() const {
    return this->velocity;
}

bool tower_defense::Bullet::refresh(Grid& g) {
	this->updateEndLocation();

	if (this->lifeTime-- == 0) {
		this->toRemove = true;
		return false;
	}

	/// reached map bounds
	if (!g.inBounds(this->location.getX(), this->location.getY())){
		this->toRemove = true;
		return false;
	}

	/// detect collision
	for (GridElement * temp : g.getElementsInRadius(this->location, this->size)){
		for (Minion * minion : temp->getMinions()){
			if (this->checkCollision(minion)) {
				minion->takeDamage(this->damage);
				if (this->hitOnlyFirst)
					this->toRemove = true;
			}


			if (this->splash != 0){
				for (GridElement* element : g.getElementsInRadius(minion, this->splash)){
					for (Minion* m : element->getMinions()){
						if (m->getSqDistance(minion) <= pow(this->splash / 2 + m->getSize() / 2, 2.0f)) {
							m->takeDamage(this->damage);
						}
					}
				}
			}
		}
	}

	this->location = endLocation;

	return true; //TODO
}

bool tower_defense::Bullet::checkCollision(tower_defense::Minion * minion){
	if (!minion) return false;

	double d = minion->getLocation().getSqDistFromSegment(location, endLocation);
	

	return pow(this->size / 2 + minion->getSize() / 2, 2.0f) > d;
}

tower_defense::Point tower_defense::Bullet::getEndLocation() const{
	return this->endLocation;
}

void tower_defense::Bullet::updateEndLocation(){
	this->endLocation = { this->location.getX() + this->velocity*sin(this->angle), this->location.getY() - this->velocity*cos(this->angle) };
}

std::string tower_defense::Bullet::toString() const {
	std::string info = std::string("Bullet: Damage: ") + std::to_string(this->damage) + " Angle: " + std::to_string(this->angle) + " Size: " + std::to_string(this->size)
		+ " LifeTime: " + std::to_string(this->lifeTime) + " Velocity: " + std::to_string(this->velocity) + " Location: " + this->location.toString();

	return info;
}

void tower_defense::Bullet::print() const{
	std::cout << this->toString() << std::endl;
}

bool tower_defense::Bullet::hits(Minion* m) {
	return false; //TODO
}