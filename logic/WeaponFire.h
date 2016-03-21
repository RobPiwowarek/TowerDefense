#ifndef WEAPON_FIRE_H
#define WEAPON_FIRE_H

#include "Entity.h"
#include "FireType.h"
#include "Minion.h"

#include <list>

namespace tower_defense
{
	/// class representing basic bullet/beam/ring or
	/// anything that is supposed to hit a minion
	class WeaponFire : public Entity
	{
	public:
		/// creates new instance of WeaponFire object
		/// using given values
		WeaponFire(const int damage, const bool hitOnlyFirst, const double splash, const double size,
			const int lifeTime, const FireType type, const double velocity, const int fireClass);
		/// creates an instance of WeaponFire object
		/// that is a copy of base
		/// and will be fired with angle modified by angleModifier
		WeaponFire(const WeaponFire& base, const double angleModifier);
		/// creates an instance of WeaponFire object
		/// that is a copy of base,
		/// located in location and directed in angle
		WeaponFire(const WeaponFire& base, const Point& location, const double angle);

		/// returns damage dealt by hit
		double getDamage() const;

		/// returns whether hits only first enemy or goes on
		bool isHitOnlyFirst() const;

		/// returns splash radius
		double getSplash() const;

		/// returns left lifetime
		double getLifeTime() const;

		/// returs velocity of the bullet/ring/...
		double getVelocity() const;

		/// refreshes object
		bool refresh(std::list<Minion*>& enemies);

		/// returns type of this object
		FireType getType() const;

	private:
		int damage;
		bool hitOnlyFirst;
		double splash;
		int lifeTime;
		double velocity;
		FireType type;

		bool hits(Minion* m);
	};
}

#endif