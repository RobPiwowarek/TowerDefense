#ifndef MINION_WAVE_MANAGER_H
#define MINION_WAVE_MANAGER_H

namespace data {
    class MinionWaveManager;
}

#include <vector>
#include "../logic/MinionWave.h"

namespace data {
    class MinionWaveManager {
    public:
        const std::string WAVE_LOCATION = "waves\\";

        // clears the manager
        void clear();

        // loads waves from (directory)(WAVE_LOCATION)*.xml
        void load(const std::string &directory, const std::vector<std::string> &waves);

        // returns minionwave with given index
        const tower_defense::MinionWave &get(int i) const;

        // returns the number of waves
        const int count() const;

    private:
        std::vector<tower_defense::MinionWave *> waves;

        tower_defense::MinionWave *loadWave(const std::string &directory, const std::string &path);

        ~MinionWaveManager();
    };
}

#endif