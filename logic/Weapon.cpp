#include "Weapon.h"


tower_defense::Weapon::Weapon(
        const double range, const int fireRate, const WeaponFireList *const weaponFireList) {
    this->fireRate = fireRate;
    this->range = range;
    this->parent = nullptr;
    this->reloading = 0;
    this->fireList = weaponFireList;
}

tower_defense::Weapon::Weapon(const Weapon &base, const Turret *const parent) {
    this->fireRate = base.fireRate;
    this->range = base.range;
    this->parent = parent;
    this->reloading = 0;
    this->fireList = base.fireList;
    this->cur = fireList->begin();
}

double tower_defense::Weapon::getRange() const {
    return this->range;
}

int tower_defense::Weapon::getFireRate() const {
    return this->fireRate;
}

int tower_defense::Weapon::getReloading() const {
    return this->reloading;
}
#include <iostream>
void tower_defense::Weapon::refresh(bool beginSequence, Map* m) {
	if (this->reloading != 0 || beginSequence) {
		while (this->cur->first == this->reloading) {
			//TODO fire

			std::cout << "fire";

			if (++cur == this->fireList->cend()) {
				this->cur = this->fireList->cbegin();
				break;
			}

		}

		if (++this->reloading == this->fireRate) this->reloading = 0;
	}
}