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
#include "Game.h"
#include "Item.h"
#include <queue>

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
        void addMinion(Minion *m);
		
		/// removes a minion from map
		void removeMinion(Game& game, Minion* m);

        /// adds a turret to map
        void addTurret(Turret *t);

        /// adds an item to map
        void addItem(Item *i);

		/// adds a weaponfire to map
		void addFire(WeaponFire* w);

        /// returns set of minions
        std::set<Minion *> &getMinions();

        /// returns set of turrets
        std::set<Turret *> &getTurrets();

        /// returns set of weaponfires
        std::set<WeaponFire *> &getWeaponFires();

        // returns set of items
        std::set<Item *> &getItems();

		/// returns minions in an area near the point
		std::set<Minion *> getMinionsNearPoint(const tower_defense::Point & point, double radius);

		/// returns minions in an area near other minion
		std::set<Minion *> getMinionsNearMinion(tower_defense::Minion * minion, double radius);

        /// returns grid
        Grid &getGrid();

		/// returns if you can place a tower on given point
		bool canPlaceTurret(const tower_defense::Point & point, const tower_defense::Turret & turret);
		bool canPlaceTurret(const double x, const double y, const tower_defense::Turret & turret);
		bool canPlaceTurret(const int x, const int y, const tower_defense::Turret & turret);


        /// refreshes all elements contained by the map
        void refresh(Game &game);

    private:
        Grid *grid;
        std::set<Minion *> minions;
        std::set<WeaponFire *> weaponFires;
        std::set<Turret *> turrets;
        std::set<Item *> items;

		bool outOfMap(const Point& p)const;
    };
}

#endif