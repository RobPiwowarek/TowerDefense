#ifndef PLAYER_H
#define PLAYER_H

namespace tower_defense {
    /// class that represents the player
    class Player {
    public:
        /// creates a player with given health and money
        Player(const int health, const int money);

        /// returns the amount of player's money
        int getMoney() const;

        /// sets player's money
        void setMoney(const int money);

        /// returns the amount of player's health
        int getHealth() const;

        /// sets player's health
        void setHealth(const int health);

    private:
        int health;
        int money;
    };
}

#endif