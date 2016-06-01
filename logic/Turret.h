#ifndef TURRET_H
#define TURRET_H

#include <list>
#include <cmath>

namespace tower_defense {
    class Turret;
}

#include "Entity.h"
#include "Minion.h"
#include "Weapon.h"
#include "Map.h"

namespace tower_defense {
    /// class that represents an anti-minion
    /// player's turret
    class Turret : public Entity {
    public:

        /// creates a new instance of turret
        /// using given values
        Turret(const int size, const int turretClass, const double rotationSpeed, const int level, const Weapon &wBase, int health, int armor = 0);

        /// creates a new instance of turret
        /// that is a copy of base located in
        /// location
        Turret(const Turret &base, const Point &location);

        ~Turret();

        /// returns turret's speed of rotation
        double getRotationSpeed() const;

        /// sets turret's speed of rotation
        void setRotationSpeed(const double d);

        /// returns current turret's level
        int getLevel() const;

        /// sets turret's level
        void setLevel(int lvl);

        /// returns current turret's health
        int getCurrentHealth() const;

        /// sets current turret's health
        void setCurrentHealth(int currentHealth);

		/// removes health from turret (counting armor) and sets flag as recently attacked
		void attack(int damage);

        /// returns current turret's max health
        int getMaxHealth() const;

        /// reduces current health by damage returns false if failed to deal damage.
        bool receiveDamage(const int damage, Grid &g);

        /// destroys turret
        void destroy(Grid &g);

        /// returns armor;
        int getArmor() const;

        /// sets armor;
        void setArmor(int armor);

		/// returns toRemove
		bool shouldBeRemoved() const;

		/// sets toRemove
		void setToRemove(const bool b);

        /// refreshes turret (and it's weapon)
        bool refresh(tower_defense::Map* map);

        /// returns turret current weapon
        Weapon &getWeapon();

		/// returns if the turret was recently attacked
		bool wasRecentlyAttacked() const;

    private:
		const int RECENTLY_ATTACKED_DEFAULT_DURATION = 2;

        Weapon *weapon;
        int level;
        int currentHealth;
        int maxHealth;
        int armor;
        double rotationSpeed;
		bool toRemove = false;
		int recentlyAttacked = 0;
    };
}

#endif