#ifndef MINION_WAVE_MANAGER_H
#define MINION_WAVE_MANAGER_H

namespace data {
	class MinionWaveManager;
}

#include <vector>;
#include "../logic/MinionWave.h"

namespace data {
	class MinionWaveManager {
	public:
		const std::string WAVE_LOCATION = "waves/";

		// clears the manager
		void clear();

		// loads waves from (GAME_FILE_LOCATION)(WAVE_LOCATION)
		void load(std::vector<std::string> waves);

		// returns minionwave with given index
		const tower_defense::MinionWave& get(int i) const;

		// returns the number of waves
		const int count() const;
	private:
		std::vector<tower_defense::MinionWave*> waves;
	};
}

#endif