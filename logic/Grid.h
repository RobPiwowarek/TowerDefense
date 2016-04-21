#ifndef GRID_H
#define GRID_H

namespace tower_defense {
    class Grid;
}

#include "GridElement.h"
#include "Map.h"

namespace tower_defense {

    class Grid {

    public:
        /// creates grid with given size
        Grid(int x, int y, Map &m);

        ~Grid();

        /// returns grid's width
        int getWidth() const;

        /// returns grid's height
        int getHeight() const;

        /// returns element
        GridElement *getElement(const Point &p) const;

        /// calculate distances
        void calculateDistance();

    private:
        int height;
        int width;
        GridElement ***elements;
        tower_defense::Map &map;
    };
}

#endif