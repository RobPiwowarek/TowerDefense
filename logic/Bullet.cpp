#include "Bullet.h"

tower_defense::Bullet::Bullet(const int damage, const double size, const bool hitOnlyFirst, const double splash,
	const int velocity, const int lifeTime, const int fireClass) 
	: WeaponFire(damage, size, lifeTime, bullet, fireClass) {
	this->hitOnlyFirst = hitOnlyFirst;
	this->splash = splash;
	this->velocity = velocity;
}

tower_defense::Bullet::Bullet(const Bullet& base, const double angleModifier) 
	: WeaponFire(base, angleModifier) {
	this->hitOnlyFirst = base.hitOnlyFirst;
	this->splash = base.splash;
	this->velocity = base.velocity;
}

tower_defense::Bullet::Bullet(const Bullet& base, const Point& location, const double angle)
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
