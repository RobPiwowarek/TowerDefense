#include "Weapon.h"
#include "Beam.h"
#include "Bullet.h"
#include "Ring.h"



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
			WeaponFire* fire = nullptr;
			
			switch(this->cur->second.first->getType()){
			case 0: 
				fire = new Bullet(this->cur->second.first->getDamage(), this->cur->second.first->getSize(), 
					dynamic_cast<tower_defense::Bullet*>(this->cur->second.first)->isHitOnlyFirst(), 
					dynamic_cast<tower_defense::Bullet*>(this->cur->second.first)->getSplash(), 
					dynamic_cast<tower_defense::Bullet*>(this->cur->second.first)->getVelocity(), 
					this->cur->second.first->getLifeTime(), 0);
				break;
			case 1:
				fire = new Beam(this->cur->second.first->getDamage(), this->cur->second.first->getSize(), 1,
					dynamic_cast<tower_defense::Beam*>(this->cur->second.first)->isHitOnlyFirst(), 
					dynamic_cast<tower_defense::Beam*>(this->cur->second.first)->getWidth());
				break;
			case 2:
				fire = new Ring(this->cur->second.first->getDamage(), 
					dynamic_cast<tower_defense::Ring*>(this->cur->second.first)->getVelocity(), 
					this->cur->second.first->getLifeTime(), 2);
				break;
			default: std::cout << "FIRE ERROR " << std::endl;
			}

			std::cout << "fire";

			if (fire != nullptr) {
				m->addFire(fire);
			}

			if (++cur == this->fireList->cend()) {
				this->cur = this->fireList->cbegin();
				break;
			}

		}

		if (++this->reloading == this->fireRate) this->reloading = 0;
	}
}