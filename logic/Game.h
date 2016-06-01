#ifndef GAME_H
#define GAME_H
namespace tower_defense {
	class Game;
}

#include "Map.h"
#include "MinionWave.h"
#include "Player.h"
#include "../graphics/menu/Menu.h"

namespace tower_defense {
    class Game {
    public:
        Game(Map *, Player *);

        ~Game();

		// returns map
        tower_defense::Map &getMap();

		// returns current wave
        tower_defense::MinionWave &getCurrentWave();

		// returns player object
        tower_defense::Player &getPlayer();

		// adds turret to the game and map etc
		void addTurret(const Turret* base, const Point& p, const int cost);

		// refreshes all the game
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
