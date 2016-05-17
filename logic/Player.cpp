#include "Player.h"

tower_defense::Player::Player(const int money) {
    this->money = money;
	this->nItems = 4;
}

int tower_defense::Player::getMoney() const {
    return this->money;
}

void tower_defense::Player::setMoney(const int money) {
    this->money = money;
}

int tower_defense::Player::getNItems() const {
	return this->nItems;
}

void tower_defense::Player::setNItems(const int n) {
	this->nItems = n;
}