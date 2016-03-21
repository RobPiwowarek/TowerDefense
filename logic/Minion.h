#ifndef MINION_H
#define MINION_H

#include "PathFollower.h"

namespace tower_defense
{
	/// class for minion objects
	class Minion : public PathFollower
	{
	public:
		/// creates a minion prototype with given values
		Minion(const double velocity, const double size, const int minionClass, const int reward, const int healt);
		/// creates a minion using given
		/// that will follow given Path
		Minion(const Minion& base, const Path* const p);
		
		/// returns reward gained for destroying this minion
		int getReward() const;

		/// returns current minion's health
		int getHealth() const;

		/// damages minion,
		/// returns health <= 0
		bool damage(int value);

	private:
		int health;
		int reward;
	};
}

#endif