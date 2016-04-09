#include "Minion.h"

tower_defense::Minion::Minion(
	const double velocity, const double size, const int minionClass, const int reward, const int health, const int damage)
	: Entity(Point(0,0), 0.0, size, minionClass) {
	this->velocity = velocity;
	this->reward = reward;
	this->health = health;
	this->next = nullptr;
}

tower_defense::Minion::Minion(const Minion& base, const Point& x0)
	:Entity(base) {
	this->velocity = base.velocity;
	this->reward = base.reward;
	this->health = base.health;
	this->location = x0;
	this->next = nullptr;
}

void tower_defense::Minion::refresh(Grid &g) {
    // TODO: choose next target/location

    //

	// Update location
    this->getLocation().setPoint(this->next->getLocation());



}

int tower_defense::Minion::getDamage() {
    return this->damage;
}

double tower_defense::Minion::getVelocity() {
    return this->velocity;
}

int tower_defense::Minion::getReward() const
{
	return this->reward;
}

int tower_defense::Minion::getHealth() const
{
	return this->health;
}

void tower_defense::Minion::setHealth(int value)
{
	this->health = value;
}
