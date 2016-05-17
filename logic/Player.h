#ifndef PLAYER_H
#define PLAYER_H

namespace tower_defense {
    /// class that represents the player
    class Player {
    public:
        /// creates a player with given health and money
        Player(const int money);

        /// returns the amount of player's money
        int getMoney() const;

        /// sets player's money
        void setMoney(const int money);
		
		/// returns number if items to protect
		int getNItems() const;

		/// sets number of items to protect
		void setNItems(const int n);

    private:
        int money;
		int nItems;
    };
}

#endif