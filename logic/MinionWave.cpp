#include "MinionWave.h"

tower_defense::MinionWave::MinionWave(const std::queue<Minion*>& minions, const int timeBetweenMinions) {
	this->minions = minions;
	this->timeToNext = this->timeBetweenMinions = timeBetweenMinions;
}

tower_defense::MinionWave::MinionWave(const MinionWave& wave) {
	this->minions = wave.minions;

	this->timeToNext = this->timeBetweenMinions = wave.timeBetweenMinions;
}

tower_defense::MinionWave::~MinionWave() {
}

std::queue<tower_defense::Minion*> tower_defense::MinionWave::getMinions() const { return this->minions; }

int tower_defense::MinionWave::getTimeBetweenMinions() const {return this->timeBetweenMinions; }

int tower_defense::MinionWave::getTimeToNextMinion() const {return this->timeToNext; }

bool tower_defense::MinionWave::finished() const {
	return this->minions.empty();
}
tower_defense::Minion* tower_defense::MinionWave::refresh() {
	if (this->timeToNext > 0 || this->finished()) {
		this->timeToNext--;
		return nullptr;
	}

	this->timeToNext = this->timeBetweenMinions;
	Minion* toRet = this->minions.front();
	this->minions.pop();
	
	return toRet;
}