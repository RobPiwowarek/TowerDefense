#ifndef MINION_WAVE_H
#define MINION_WAVE_H

#include <queue>

namespace tower_defense {
    class MinionWave;
}

#include "Minion.h"

namespace tower_defense {
    /// class for wave of minions
    class MinionWave {
    public:
        /// creates new wave with given time between minion spawns
        /// minion objects must be allocated with new keyword
        MinionWave(const std::queue<Minion *> &minions, const int timeBetweenMinions);

        //TODO copying constructor
        ~MinionWave();

        /// returns if the last minion was already returned
        bool finished() const;

        /// refreshes wave
        /// returns pointer to minion that is to be spawned
        /// or nullptr if none
        /// minion must be deleted after their no longer used
        Minion *refresh();

    private:
        std::queue<Minion *> minions;
        int timeToNext;
        int timeBetweenMinions;
    };
}

#endif