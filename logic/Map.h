#ifndef MAP_H
#define MAP_H

#include <set>

namespace tower_defense {
	class Map;
}

#include "Point.h"
#include "Turret.h"
#include "Grid.h"
#include "Minion.h"
#include "WeaponFire.h"
#include "Player.h"

namespace tower_defense {
	class Map {
	public:
		/// creates a new map with given size
		Map(const int width, const int height);
		~Map();
		/// returns map's width
		double getWidth() const;
		/// returns map's height
		double getHeight() const;

		/// adds a minion to map
		void addMinion(Minion* m);
		/// adds a turret to map
		void addTurret(Turret* t, Point p);

		/// returns set of minions
		std::set<Minion*>& getMinions();
		/// returns set of turrets
		std::set<Turret*>& getTurrets();
		/// returns set of weaponfires
		std::set<WeaponFire*>& getWeaponFires();

		/// refreshes all elements contained by the map
		void refresh(Player& p);

	private:
		Grid* grid;
		std::set<Minion*> minions;
		std::set<WeaponFire*> weaponFires;
		std::set<Turret*> turrets;
	};
}

#endif