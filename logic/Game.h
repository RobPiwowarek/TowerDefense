#ifndef GAME_H
#define GAME_H

#include "Map.h"
#include "MinionWave.h"

namespace tower_defense {
    class Game {
    public:
        Game(Map *, Player *);

        ~Game();

        tower_defense::Map &getMap();

        tower_defense::MinionWave &getCurrentWave();

        tower_defense::Player &getPlayer();

        void refresh();

    private:
        Map *map;
        int curWave;
        MinionWave *wave;
        Player *player;
    };

}
#endif
