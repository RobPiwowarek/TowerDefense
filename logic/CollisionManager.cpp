#include <cmath>
#include "CollisionManager.h"

bool tower_defense::CollisionManager::CheckCollision() {

    // TODO: wez 2 obiekty z tablic, 1 minion, 1 pocisk i sprawdz czy
    // (promien miniona + promien pocisku)^2 >= getSqDistance miedzy nimi

    for (int i = 0; i < this->bullets.size(); i++) {
        Entity *bullet = &this->bullets[i];
        double bullet_size = bullet->getSize();

        for (int j = 0; j < this->minions.size(); j++) {
            Entity minion = this->minions[j];
            double minion_size = minion.getSize();

            if (pow((bullet_size + minion_size), 2.0f) >= minion.getSqDistance(bullet)) {
                // mamy kolizje!
            }


        }
    }

	return false;
}