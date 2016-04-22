#ifndef TOWERDEFENSE_ITEM_H
#define TOWERDEFENSE_ITEM_H

#include "Entity.h"

namespace tower_defense {
    class Item;
}

namespace tower_defense {
    class Item : public Entity {

    public:
        Item(const tower_defense::Point &location, const double angle, const double size, const int itemClass);

        int getLife() const;

    private:
        const int playerLife = 25; // how much life it will take from player

    };
}

#endif
