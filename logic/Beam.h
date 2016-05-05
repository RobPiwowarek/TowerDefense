#ifndef BEAM_H
#define BEAM_H

namespace tower_defense {
    class Beam;
}

#include "WeaponFire.h"
#include "Minion.h"

namespace tower_defense {
    class Beam : public WeaponFire {
    public:
        /// creates new instance of Beam object
        /// using given values
        Beam(const int damage, const double maxSize, const int fireClass, const bool hitOnlyFrst);

        /// creates an instance of Beam object
        /// that is a copy of base
        /// and will be fired with angle modified by angleModifier
        Beam(const Beam &base, const double angleModifier);

        /// creates an instance of Beam object
        /// that is a copy of base,
        /// located in location and directed in angle
        Beam(const Beam &base, const Point &location, const double angle);

        /// returns if beam hits only first target in line
        bool isHitOnlyFirst() const;

        /// refreshes the beam
        bool refresh(Grid& grid);

		/// check collision
		bool checkCollision(tower_defense::Minion * minion);

    private:
        bool hitOnlyFirst;

        bool hits(Minion* m);
    };
}

#endif