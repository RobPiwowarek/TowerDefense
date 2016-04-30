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
        /// helper enum in calculateDistance()
        enum Target {
            Turret,
            Item
        };

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
        void calculateDistance(const Target target);

        /// helper function for function pointers in calculateDistance()
        void calcDistItems(std::priority_queue<std::pair<int, GridElement*>> &initialNodes);

        /// helper function for function pointers in calculateDistnace()
        void calcDistTurrets(std::priority_queue<std::pair<int, GridElement*>> &initialNodes);


    private:
        int height;
        int width;
        GridElement ***elements;
        tower_defense::Map &map;


    };
}

#endif