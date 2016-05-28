#ifndef GRID_ELEMENT_H
#define GRID_ELEMENT_H

#include <set>

namespace tower_defense {
    class GridElement;
}

#include "Minion.h"
#include "Point.h"
#include "Turret.h"
#include "Item.h"
#include "WeaponFire.h"

namespace tower_defense {
    class GridElement {
    public:
        /// creates an object at given location
        GridElement(const Point &location, Grid &g);

        /// returns distance to the closest target
        int getDistToTarget() const;

        /// sets distance to the closest target
        void setDistToTarget(const int dist);

		/// returns distance to the closest corner
		int getDistToCorner() const;

		/// sets distance to the closest corner
		void setDistToCorner(const int dist);

		/// returns distance to the closest edge
		int getDistToEdge() const;

		/// sets distance to the closest edge
		void setDistToEdge(const int dist);

        /// returns distance to the closest turret
        int getDistToTurret() const;

        /// sets distance to the closest turret
        void setDistToTurret(const int dist);

        /// returns turret at the current grid element
        Turret *getTurret();

        /// sets turret at the current grid element
        /// returns false if failed to set turret
        bool setTurret(Turret *t);

        /// returns minions at the current grid element
        std::set<Minion *> &getMinions();

        /// returns location of the grid element
        Point getLocation() const;

        /// these methods return grid elements next to this one
        GridElement *getLeftNeighbour() const;

        GridElement *getRightNeighbour() const;

        GridElement *getUpNeighbour() const;

        GridElement *getDownNeighbour() const;

        /// returns false if turret isn't present
        bool hasTurret() const;

        /// returns item
        Item& getItem() const;

        /// checks if element has item.
        bool hasItem() const;

        /// checks if element has specific item
        bool hasItem(Item * item) const;

        /// sets item
        void setItem(Item * item);

        /// adds minion to grid element
        void addMinion(Minion* m);

        /// removes minion from grid element
        void removeMinion(Minion* m);

    private:
        Point location;
        int distToTarget = -1;
        int distToTurret = -1;
		int distToCorner = -1;
		int distToEdge = -1;
        bool occupied = false; // has turret?

        Grid &grid;
        Item *item = nullptr;
        Turret *turret = nullptr;
        std::set<Minion *> minions;
    };
}
#endif