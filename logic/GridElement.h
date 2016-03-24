#ifndef GRID_ELEMENT_H
#define GRID_ELEMENT_H

#include <set>

namespace tower_defense {
	class GridElement;
}
#include "Minion.h"
#include "Point.h"

namespace tower_defense {
	class GridElement 
	{
	public:
		/// creates an object at given location
		GridElement(const Point& location);

		/// returns distance to the closest target
		int getDistToTarget() const;
		/// sets distance to the closest target
		void setDistToTarget(const int dist);

		/// returns distance to the clostst turret
		int getDistToTurret() const;
		/// sets distance to the closest turret
		void setDistToTurret(const int dist);

		/// returns minions at the current grid element
		std::set<Minion*>& getMinions();

		/// returns location of the grid element
		Point getLocation() const;

	private:
		Point location;
		int distToTarget;
		int distToTurret;

		std::set<Minion*> minions;
	};
}
#endif