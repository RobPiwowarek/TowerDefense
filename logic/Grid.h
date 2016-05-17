#ifndef GRID_H
#define GRID_H

namespace tower_defense {
    class Grid;
}

#include "GridElement.h"
#include "Map.h"
#include <queue>
#include <xfunctional>

namespace tower_defense {
	#define _calcDistNode std::pair<int, GridElement*>
	#define _calcDistNodeQueue std::priority_queue <_calcDistNode, std::vector<_calcDistNode>, std::greater<_calcDistNode>>

	class Grid {

    public:
        /// helper enum in calculateDistance()
        enum Target {
            Turret,
            Item,
			Escape
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

		/// returns element
		GridElement *getElement(const double x, const double y) const;

        /// calculate distances
        void calculateDistance(const Target target);

        /// helper function in calculateDistance()
		void calcDistItems(_calcDistNodeQueue &initialNodes);

        /// helper function in calculateDistance()
		void calcDistTurrets(_calcDistNodeQueue &initialNodes);

		/// helper function in calculateDistance()
		void calcDistEscapeCorners(_calcDistNodeQueue &initialNodes);

		/// helper function in calculateDistance()
		void calcDistEscapeEdges(_calcDistNodeQueue &initialNodes);

		/// returns grid elements in a radius from a Point
		std::set<GridElement*> getElementsInRadius(const Point & p, double radius) const;

		/// returns grid elements in a radius from a Minion
		std::set<GridElement*> getElementsInRadius(Minion * minion, double radius) const;

		/// returns grid elements in a line given by starting point and ending point
		std::set<GridElement*> getElementsInLine(const Point & startingPoint, const Point & endingPoint) const;

    private:
        int height;
        int width;
        GridElement ***elements;
        tower_defense::Map &map;

		inline void tower_defense::Grid::calculateDistance_checkNeighbour(const tower_defense::Grid::Target target,
			tower_defense::GridElement* neighbour,
			_calcDistNode& node,
			_calcDistNodeQueue& nodes);
    };
}

#endif