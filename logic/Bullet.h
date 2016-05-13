#ifndef BULLET_H
#define BULLET_H

namespace tower_defense {
    class Bullet;
}

#include "WeaponFire.h"
#include "Minion.h"
#include "Grid.h"

namespace tower_defense {
    class Bullet : public WeaponFire {
    public:
        /// creates new instance of Beam object
        /// using given values
        Bullet(const int damage, const double size, const bool hitOnlyFirst, const double splash,
               const double velocity, const int lifeTime, const int fireClass, const double splashRadius);

        /// creates an instance of Beam object
        /// that is a copy of base
        /// and will be fired with angle modified by angleModifier
        Bullet(const Bullet &base, const double angleModifier);

        /// creates an instance of Beam object
        /// that is a copy of base,
        /// located in location and directed in angle
        Bullet(const Bullet &base, const Point &location, const double angle);

        /// returns if the bullet can hit only the first object on its way
        bool isHitOnlyFirst() const;

        /// returns the size of area where the minions will be damaged
        double getSplash() const;

        /// returns the velocity of the bullet
        double getVelocity() const;

        /// refreshes object
        bool refresh(Grid& grid);

		/// checks if collision occured with a minion
		bool checkCollision(tower_defense::Minion * minion);

    private:
        bool hitOnlyFirst;
        double splash;
		double splashRadius;
        double velocity;

        bool hits(Minion* m);
    };
}

#endif