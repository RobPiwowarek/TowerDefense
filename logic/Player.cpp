#include "Player.h"

tower_defense::Player::Player(const int health, const int money)
{
	this->health = health;
	this->money = money;
}

int tower_defense::Player::getMoney() const
{
	return this->money;
}

void tower_defense::Player::setMoney(const int money)
{
	this->money = money;
}

int tower_defense::Player::getHealth() const
{
	return this->health;
}

void tower_defense::Player::setHealth(const int health)
{
	this->health = health;
}