#include "Player.h"

tower_defense::Player::Player(const int money) {
    this->money = money;
}

int tower_defense::Player::getMoney() const {
    return this->money;
}

void tower_defense::Player::setMoney(const int money) {
    this->money = money;
}
