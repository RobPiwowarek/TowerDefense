#ifndef GAME_H
#define GAME_H
namespace tower_defense {
	class Game;
}

#include "Map.h"
#include "MinionWave.h"
#include "Player.h"


namespace tower_defense {
    class Game {
    public:
        Game(Map *, Player *);

        ~Game();

        tower_defense::Map &getMap();

        tower_defense::MinionWave &getCurrentWave();

        tower_defense::Player &getPlayer();

		void addTurret(const Turret* base, const Point& p, const int cost);

        void refresh();

    private:
		void refreshWave();

        tower_defense::Map *map;
        int curWave;
        tower_defense::MinionWave *wave;
        tower_defense::Player *player;
    };

}
#endif
