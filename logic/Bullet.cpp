#include "Bullet.h"
#include <iostream>


tower_defense::Bullet::Bullet(const int damage, const double size, const bool hitOnlyFirst, const double splash,
                              const double velocity, const int lifeTime, const int fireClass, const double splashRadius)
        : WeaponFire(damage, size, lifeTime, bullet, fireClass) {
    this->hitOnlyFirst = hitOnlyFirst;
    this->splash = splash;
    this->velocity = velocity;
	this->splashRadius = splashRadius;
}

tower_defense::Bullet::Bullet(const Bullet &base, const double angleModifier)
        : WeaponFire(base, angleModifier) {
    this->hitOnlyFirst = base.hitOnlyFirst;
    this->splash = base.splash;
    this->velocity = base.velocity;
	this->splashRadius = base.splashRadius;
}

tower_defense::Bullet::Bullet(const Bullet &base, const Point &location, const double angle)
        : WeaponFire(base, location, angle) {
    this->hitOnlyFirst = base.hitOnlyFirst;
    this->splash = base.splash;
    this->velocity = base.velocity;
	this->splashRadius = base.splashRadius;
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

	/// detect collision
	tower_defense::GridElement * temp = g.getElement(this->location);

	if (!temp->getMinions().empty()){
		for (tower_defense::Minion* minion : temp->getMinions()){
			if (this->checkCollision(minion)){
				if (!this->splashRadius){
					for (GridElement* element : g.getElementsInRadius(minion, this->splashRadius)){
						for (Minion* m : element->getMinions()){
							if (m->getSqDistance(minion) <= pow(this->splashRadius, 2.0f)){
								m->takeDamage(this->damage);
							}
						}
					}
				}

				minion->takeDamage(this->damage); // damage the main minion

				if (this->hitOnlyFirst){

					/// TODO: usun po kolizji
				}

				std::cout << "KOLIZJA" << std::endl;

				/// mozna trafione miniony gdzies zachowac i dalej z nimi cos zrobic

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