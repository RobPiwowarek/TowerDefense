//
// Created by aaron on 19.03.16.
//

#ifndef TOWERDEFENSE_COLLISIONMANAGER_H
#define TOWERDEFENSE_COLLISIONMANAGER_H

#include <vector>
#include "Entity.h"

namespace tower_defense {
    class CollisionManager {
        // singleton
        static CollisionManager *instance;


        // TODO: tablica przechowujaca aktualnie znajdujace sie miniony na mapie, tak samo pociski
        std::vector<Entity> bullets;
        std::vector<Entity> minions;

    public:
        bool CheckCollision();

        virtual ~CollisionManager() { }

        CollisionManager() { }

        static CollisionManager *getInstance() {
            if (!instance)
                instance = new CollisionManager();
            return instance;
        }

        const std::vector<Entity> &getBullets() const {
            return bullets;
        }


        const std::vector<Entity> &getMinions() const {
            return minions;
        }

    };
}

#endif //TOWERDEFENSE_COLLISIONMANAGER_H
