//
// Created by aaron on 19.03.16.
//

#ifndef TOWERDEFENSE_COLLISIONMANAGER_H
#define TOWERDEFENSE_COLLISIONMANAGER_H

namespace tower_defense {
    class CollisionManager {
        // singleton
        static CollisionManager *instance;


        // TODO: tablica przechowujaca aktualnie znajdujace sie miniony na mapie, tak samo pociski


    public:
        bool CheckCollision();

        virtual ~CollisionManager() { }

        CollisionManager() { }

        static CollisionManager *getInstance() {
            if (!instance)
                instance = new CollisionManager();
            return instance;
        }


    };
}

#endif //TOWERDEFENSE_COLLISIONMANAGER_H
