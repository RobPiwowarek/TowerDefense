#include "Weapon.h"


tower_defense::Weapon::Weapon(const double range, const int fireRate, const int objClass)
{
	this->fireRate = fireRate;
	this->range = range;
	this->parent = nullptr;
	this->reloading = 0;
	this->objClass = objClass;
}

tower_defense::Weapon::Weapon(const Weapon& base, const Turret* const parent)
{
	this->fireRate = base.fireRate;
	this->range = base.range;
	this->parent = parent;
	this->reloading = 0;
	this->objClass = base.objClass;
}

double tower_defense::Weapon::getRange() const
{
	return this->range;
}

int tower_defense::Weapon::getFireRate() const
{
	return this->fireRate;
}

int tower_defense::Weapon::getReloading() const
{
	return this->reloading;
}

int tower_defense::Weapon::getClass() const
{
	return this->objClass;
}
