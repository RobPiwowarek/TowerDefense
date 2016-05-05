#include "Bullet.h"


tower_defense::Bullet::Bullet(const int damage, const double size, const bool hitOnlyFirst, const double splash,
                              const double velocity, const int lifeTime, const int fireClass)
        : WeaponFire(damage, size, lifeTime, bullet, fireClass) {
    this->hitOnlyFirst = hitOnlyFirst;
    this->splash = splash;
    this->velocity = velocity;
}

tower_defense::Bullet::Bullet(const Bullet &base, const double angleModifier)
        : WeaponFire(base, angleModifier) {
    this->hitOnlyFirst = base.hitOnlyFirst;
    this->splash = base.splash;
    this->velocity = base.velocity;
}

tower_defense::Bullet::Bullet(const Bullet &base, const Point &location, const double angle)
        : WeaponFire(base, location, angle) {
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

	/// detect collision
	tower_defense::GridElement * temp = g.getElement(this->location);

	if (!temp->getMinions().empty()){
		for (tower_defense::Minion* minion : temp->getMinions()){
			if (this->checkCollision(minion)){
				/// mamy kolizje
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