#include "Minion.h"

tower_defense::Minion::Minion(const double velocity, const double size, const int minionClass, const int reward, const int healt)
	: PathFollower(velocity, size, minionClass)
{
	this->reward = reward;
	this->health = health;
}

tower_defense::Minion::Minion(const Minion& base, const Path* const p)
	:PathFollower(base, p)
{
	this->reward = base.reward;
	this->health = base.health;
}

int tower_defense::Minion::getReward() const
{
	return this->reward;
}

int tower_defense::Minion::getHealth() const
{
	return this->health;
}

bool tower_defense::Minion::damage(int value)
{
	return (this->health -= value) <= 0;
}
