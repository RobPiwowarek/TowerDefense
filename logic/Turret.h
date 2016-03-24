#ifndef TURRET_H
#define TURRET_H

#include <list>

namespace tower_defense {
	class Turret;
}
#include "Entity.h"
#include "Minion.h"
#include "Weapon.h"

namespace tower_defense {
	/// class that represents an anti-minion
	/// player's turret
	class Turret : public Entity
	{
	public:

		/// creates a new instance of turret
		/// using given values
		Turret(const int size, const int turretClass, const double rotationSpeed, const int level, const Weapon& wBase);
		/// creates a new instance of turret
		/// that is a copy of base located in
		/// location
		Turret(const Turret& base, const Point& location);
		~Turret();

		/// returns turret's speed of rotation
		double getRotationSpeed() const;
		/// sets turret's speed of rotation
		void setRotationSpeed(const double d);

		/// returns current turret's level
		int getLevel() const;
		/// sets turret's level
		void setLevel(int lvl);

		/// refreshes turret (and it's weapon)
		bool refresh(std::list<Minion*> enemies);

		/// returns turret current weapon
		Weapon& getWeapon();

	private:
		Weapon* weapon;
		int level;
		double rotationSpeed;
	};
}

#endif