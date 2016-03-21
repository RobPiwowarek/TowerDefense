#ifndef WEAPON_H
#define WEAPON_H

#include "Minion.h";
#include "Turret.h";

#include <list>

namespace tower_defense
{
	/// class for objects that represent turret's weapons
	class Weapon
	{
	public:
		/// creates an instance of Weapon object
		/// using given values
		Weapon(const double range, const int fireRate, const int objClass);
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

		/// refreshes weapon
		bool refresh(const std::list<Minion*>& enemies);

	private:
		double range;
		int fireRate;
		int reloading;
		int objClass;
		const Turret* parent;
	};

}

#endif