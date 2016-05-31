#ifndef RING_H
#define RING_H

namespace tower_defense {
    class Ring;
}

#include "WeaponFire.h"
#include <string>

namespace tower_defense {
    class Ring : public WeaponFire {
    public:
        /// creates new instance of Ring object
        /// using given values
        Ring(const int damage, const double velocity,
			const int lifeTime, const int fireClass, const double innerRadius);

        /// creates an instance of Ring object
        /// that is a copy of base,
        /// located in location and directed in angle
		Ring(const Ring &base, const Point &location, const double angle, const double angleModifier);

        /// returns the ring's velocity
        double getVelocity() const;

		/// return object info in a string
		std::string toString() const;

		/// print object info to standard output
		void print() const;

        /// refreshes the ring
        bool refresh(Grid& grid);

		/// check collision
		bool checkCollision(tower_defense::Minion * minion);

		/// returns inner radius
		double getInnerRadius() const;

		/// sets inner radius
		void setInnerRadius(const double r);

    private:
        double velocity;
		double innerRadius;

        bool hits(Minion* m);
    };
}

#endif