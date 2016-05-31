#ifndef BEAM_H
#define BEAM_H

namespace tower_defense {
    class Beam;
}

#include "WeaponFire.h"
#include "Minion.h"
#include <string>

namespace tower_defense {
    class Beam : public WeaponFire {
    public:
        /// creates new instance of Beam object
        /// using given values
        Beam(const int damage, const double maxSize, const int fireClass, const bool hitOnlyFrst, const double width);

        /// creates an instance of Beam object
        /// that is a copy of base,
        /// located in location and directed in angle
		Beam(const Beam &base, const Point &location, const double angle, const double angleModifier);

        /// returns if beam hits only first target in line
        bool isHitOnlyFirst() const;

        /// refreshes the beam
        bool refresh(Grid& grid);

		/// return object info in a string
		std::string toString() const;

		/// print object info to standard output
		void print() const;

		/// check collision
		bool checkCollision(tower_defense::Minion * minion);

		/// returns width 
		double getWidth() const;

		/// sets width
		void setWidth(const double width);

		/// returns endLocation
		Point getEndLocation() const;

    private:
        bool hitOnlyFirst;
		double width;
		Point endLocation;
        bool hits(Minion* m);

		/// updates end location
		void updateEndLocation();

		/// sets end location
		void setEndLocation(const Point& p);
		void setEndLocation(const int x, const int y);
		void setEndLocation(const double x, const double y);
    };
}

#endif