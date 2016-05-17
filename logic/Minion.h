#ifndef MINION_H
#define MINION_H

namespace tower_defense {
    class Minion;
}

#include "Entity.h"
#include "Grid.h"
#include "../threading/AppModel.h"
#include "../logic/Game.h"
#include "Game.h"
#include "Item.h"
#include <cmath>
#include "../logic/Point.h"

namespace tower_defense {
    /// class for minion objects
    class Minion : public Entity {
    public:
        enum TargetPriority {
            Turret,
            Item,
            Closer,
			Escape
        };

        /// creates a minion prototype with given values
        Minion(const double velocity, const double size, const int minionClass, const int reward,
               const int health, const int damage, const TargetPriority priority);

        /// creates a minion using given
        /// that will follow given Path
        Minion(const Minion &base, const Point &x0);

        void attack(tower_defense::Turret &turret) const;

		/// returns true if minion got damaged in the process
		bool takeDamage(const double damage);

        /// kills the minion
        void death(Game &game);

        /// returns reward gained for destroying this minion
        int getReward() const;

        /// returns current minion's health
        int getHealth() const;

        /// sets minion health
        void setHealth(int value);

        /// returns damage dealt by minion attack
        int getDamage() const;

        /// returns velocity of a minion
        double getVelocity() const;

        /// checks if minion is alive
        bool isDead() const;

        /// refreshes minion
        void refresh(Grid &g, Game &game);

        /// chooses next destination
		void chooseDestination(Grid &g, Game &game);

        /// returns true if has item
        bool hasItem() const;

        /// returns true if has specific item
        bool hasItem(tower_defense::Item* item) const;

        /// returns item
        tower_defense::Item * getItem() const;

        /// sets held item, returns false if failed to set
        bool setItem(tower_defense::Item* item);
    private:
        int health;
        int reward;
        int damage;

        int attackSpeed;
        int attackRefreshing;
        double velocity;

        bool dead = false;

        GridElement *next;
        tower_defense::Item *item = nullptr;
        TargetPriority target;
    };
}

#endif