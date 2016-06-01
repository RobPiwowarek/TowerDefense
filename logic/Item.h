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

        // minion picks up the item
        bool pickUp(tower_defense::Minion* minion, tower_defense::Grid& grid);

        // drop the item
        bool drop();

        // returns held
        bool isHeld() const;

        // returns playerLife
        int getLife() const;

        // returns holding minion
        tower_defense::Minion *getHoldingMinion();

    private:
        const int playerLife = 25; // how much life it will take from player
        bool held = false;
        tower_defense::Minion *holdingMinion = nullptr;
    };
}

#endif
