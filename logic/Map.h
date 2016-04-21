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

        /// adds a turret to map
        void addTurret(Turret *t, Point p);

        /// adds an item to map
        void addItem(Item *i);


        /// returns set of minions
        std::set<Minion *> &getMinions();

        /// returns set of turrets
        std::set<Turret *> &getTurrets();

        /// returns set of weaponfires
        std::set<WeaponFire *> &getWeaponFires();

        // returns set of items
        std::set<Item *> &getItems();

        /// returns grid
        Grid &getGrid();

        /// refreshes all elements contained by the map
        void refresh(Game &game);

    private:
        Grid *grid;
        std::set<Minion *> minions;
        std::set<WeaponFire *> weaponFires;
        std::set<Turret *> turrets;
        std::set<Item *> items;
    };
}

#endif