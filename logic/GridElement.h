#ifndef GRID_ELEMENT_H
#define GRID_ELEMENT_H

#include <set>

namespace tower_defense {
    class GridElement;
}

#include "Minion.h"
#include "Point.h"
#include "Turret.h"

namespace tower_defense {
    class GridElement {
    public:
        /// creates an object at given location
        GridElement(const Point &location, Grid &g);

        /// returns distance to the closest target
        int getDistToTarget() const;

        /// sets distance to the closest target
        void setDistToTarget(const int dist);

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

    private:
        Point location;
        int distToTarget;
        int distToTurret;
        bool occupied = false; // has turret?

        const Grid &grid;
        Turret *turret = nullptr; //TODO: is it really neccessary?
        std::set<Minion *> *minions;
    };
}
#endif