#ifndef MINION_H
#define MINION_H

namespace tower_defense {
	class Minion;
}
#include "Entity.h"
#include "Grid.h"

namespace tower_defense
{
	/// class for minion objects
	class Minion : public Entity
	{
	public:
		/// creates a minion prototype with given values
		Minion(const double velocity, const double size, const int minionClass, const int reward, const int health, const int damage);
		/// creates a minion using given
		/// that will follow given Path
		Minion(const Minion& base, const Point& x0);
		
		/// returns reward gained for destroying this minion
		int getReward() const;

		/// returns current minion's health
		int getHealth() const;

		/// sets minion health
		void setHealth(int value);
		
		/// returns damage dealt by minion attack
		int getDamage();

		/// returns velocity of a minion
		double getVelocity();

		/// refreshes minion
		void refresh(Grid& g);

		/// chooses next destination
		void chooseDestination(Grid& g);

	private:
		int health;
		int reward;
		int damage;

		int attackSpeed;
		int attackRefreshing;
		double velocity;

		GridElement* next;
	};
}

#endif