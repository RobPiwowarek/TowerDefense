#ifndef TOWERDEFENSE_GAME_H
#define TOWERDEFENSE_GAME_H

#include "Map.h"
#include "MinionWave.h"

namespace tower_defense {
    class Game {
    public:
        Game(Map, MinionWave, Player);
        ~Game();
        tower_defense::Map& getMap();
        tower_defense::MinionWave& getCurrentWave();
        tower_defense::Player& getPlayer();

        void refresh();

    private:
        Map map;
        MinionWave wave;
        Player player;
    };

}
#endif //TOWERDEFENSE_GAME_H
