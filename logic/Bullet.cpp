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
	this->location.setX(this->location.getX() + this->velocity*sin(this->angle));
	this->location.setY(this->location.getY() - this->velocity*cos(this->angle));

	/// reached map bounds
	if (!g.inBounds(this->location.getX(), this->location.getY())){
		this->toRemove = true;
	}

	/// detect collision
	tower_defense::GridElement * temp = g.getElement(this->location);

	if (!temp->getMinions().empty()){
		for (tower_defense::Minion* minion : temp->getMinions()){
			if (this->checkCollision(minion)){
				if (!this->splash){
					for (GridElement* element : g.getElementsInRadius(minion, this->splash)){
						for (Minion* m : element->getMinions()){
							if (m->getSqDistance(minion) <= pow(this->splash, 2.0f)){
								m->takeDamage(this->damage);
							}
						}
					}
				}

				minion->takeDamage(this->damage); // damage the main minion

				if (this->hitOnlyFirst){
					this->toRemove = true;
				}
				
				std::cout << "KOLIZJA" << std::endl;
			}
		}
	}

	return false; //TODO
}

bool tower_defense::Bullet::checkCollision(tower_defense::Minion * minion){
	if (!minion) return false;

	if (pow((this->size + minion->getSize()), 2.0f) >= minion->getSqDistance(this)){
		return true;
	}

	return false;
}

bool tower_defense::Bullet::hits(Minion* m) {
	return false; //TODO
}