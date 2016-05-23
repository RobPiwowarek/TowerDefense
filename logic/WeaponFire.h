#ifndef WEAPON_FIRE_H
#define WEAPON_FIRE_H

#include <list>

namespace tower_defense {
    class WeaponFire;
}

#include "Entity.h"
#include "FireType.h"
#include "Minion.h"
#include "Grid.h"

namespace tower_defense {
    /// class representing basic bullet/beam/ring or
    /// anything that is supposed to hit a minion
    class WeaponFire : public Entity {
    public:

        /// returns damage dealt by hit
        double getDamage() const;

        /// returns left lifetime
        double getLifeTime() const;

        /// returs velocity of the bullet/ring/...
        double getVelocity() const;

        /// refreshes object
        virtual bool refresh(Grid &grid) = 0;

        /// returns type of this object
        FireType getType() const;

		/// returns toRemove
		bool shouldBeRemoved() const;

		/// sets toRemove
		void setToRemove(const bool b);

		/// checks collision with minion
		virtual bool checkCollision(tower_defense::Minion * minion) = 0;

    protected:

        /// creates new instance of WeaponFire object
        /// using given values
        WeaponFire(const int damage, const double size,
                   const int lifeTime, const FireType type, const int fireClass);

        /// creates an instance of WeaponFire object
        /// that is a copy of base,
        /// located in location and directed in angle
        /// and will be fired with angle modified by angleModifier
		WeaponFire(const WeaponFire &base, const Point &location, const double angle, const double angleModifier);

        int damage;
        int lifeTime;
		bool toRemove = false;
        Minion *target = nullptr;
        FireType type;

        virtual bool hits(Minion *m) = 0;
    };
}

#endif