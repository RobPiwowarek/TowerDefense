#ifndef TOWERDEFENSE_ITEM_H
#define TOWERDEFENSE_ITEM_H

namespace tower_defense {
    class Item;
}

#include "Entity.h"
#include "Game.h"

namespace tower_defense {
    class Item : public Entity {

    public:
        Item(const tower_defense::Point &location, const double angle, const double size, const int itemClass);

        bool pickUp(tower_defense::Minion* minion, tower_defense::Grid& grid);

        bool drop(tower_defense::Point& location);

        bool isHeld() const;

        int getLife() const;

    private:
        const int playerLife = 25; // how much life it will take from player
        bool held = false;
    };
}

#endif
