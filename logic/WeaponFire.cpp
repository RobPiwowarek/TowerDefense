#include "WeaponFire.h"


tower_defense::WeaponFire::WeaponFire(const int damage, const bool hitOnlyFirst, const double splash, const double size,
	const int lifeTime, const tower_defense::FireType type, const double velocity, const int fireClass)
	: Entity(Point(), 0, size, fireClass)
{
	this->damage = damage;
	this->hitOnlyFirst = hitOnlyFirst;
	this->splash = splash;
	this->lifeTime = lifeTime;
	this->type = type;
	this->velocity = velocity;
}

tower_defense::WeaponFire::WeaponFire(const WeaponFire& base, const double angleModifier)
	: Entity(base)
{
	this->damage = base.damage;
	this->hitOnlyFirst = base.hitOnlyFirst;
	this->splash = base.splash;
	this->lifeTime = base.lifeTime;
	this->type = base.type;
	this->velocity = base.velocity;
	this->angle += angleModifier;
}

tower_defense::WeaponFire::WeaponFire(const WeaponFire& base, const Point& location, const double angle)
	: WeaponFire(base, angle)
{
	this->location = location;
}

double tower_defense::WeaponFire::getDamage() const
{
	return this->damage;
}

bool tower_defense::WeaponFire::isHitOnlyFirst() const
{
	return this->hitOnlyFirst;
}

double tower_defense::WeaponFire::getSplash() const
{
	return this->splash;
}

double tower_defense::WeaponFire::getLifeTime() const
{
	return this->lifeTime;
}

double tower_defense::WeaponFire::getVelocity() const
{
	return this->velocity;
}

tower_defense::FireType tower_defense::WeaponFire::getType() const
{
	return this->type;
}