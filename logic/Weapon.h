#ifndef WEAPON_H
#define WEAPON_H

#include <list>

namespace tower_defense {
	class Weapon;
}

#include "Minion.h"
#include "Turret.h"
#include "WeaponFire.h"
#include "Bullet.h"
#include "Ring.h"
#include "Beam.h"

typedef std::list<std::pair<int, tower_defense::WeaponFire*> > WeaponFireList;

namespace tower_defense {

	/// class for objects that represent turret's weapons
	class Weapon
	{
	public:
		/// creates an instance of Weapon object
        /// using given values
		/// weaponFireList is list of weapon fires,
		/// sorted by fire time in weapon cycle
		/// highest time must be lower than fireRate
		Weapon(const double range, const int fireRate, const int objClass,
			const WeaponFireList* const weaponFireList);
		/// creates an exact copy of base
		/// with given parent
		Weapon(const Weapon& base, const Turret* const parent);

		/// returns weapon's maximum range
		double getRange() const;

		/// returns firing rate of weapon
		int getFireRate() const;

		/// returns time left to reload a weapon
		int getReloading() const;

		/// returns weapon's type
		int getClass() const;

		/// shoots at target enemy
		bool shoot(Minion* target) const;

		/// refreshes weapon
		bool refresh(const std::list<Minion*>& enemies);

	private:
		const WeaponFireList* fireList;
		WeaponFireList::const_iterator cur;

		double range;
		int fireRate;
		int reloading;
		int objClass;
		const Turret* parent;
	};

}

#endif