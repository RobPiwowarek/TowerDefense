#ifndef RING_H
#define RING_H

namespace tower_defense {
    class Ring;
}

#include "WeaponFire.h"

namespace tower_defense {
    class Ring : public WeaponFire {
    public:
        /// creates new instance of Ring object
        /// using given values
        Ring(const int damage, const double velocity,
			const int lifeTime, const int fireClass);

        /// creates an instance of Ring object
        /// that is a copy of base,
        /// located in location and directed in angle
		Ring(const Ring &base, const Point &location, const double angle, const double angleModifier);

        /// returns the ring's velocity
        double getVelocity() const;

        /// refreshes the ring
        bool refresh(Grid& grid);

		/// check collision
		bool checkCollision(tower_defense::Minion * minion);

    private:
        double velocity;

        bool hits(Minion* m);
    };
}

#endif