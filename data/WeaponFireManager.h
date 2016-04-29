#ifndef WEAPON_FIRE_MANAGER_H
#define WEAPON_FIRE_MANAGER_H

namespace data {
	class WeaponFireManager;
}

#include <map>
#include "../logic/WeaponFire.h"
#include "../include/SFML/Graphics.hpp"

namespace data {
	class WeaponFireManager {
	public:
		const std::string WEAPON_FIRES_LOCATION = "fires\\";

		WeaponFireManager();
		~WeaponFireManager();

		// returns weapon fire with given class
		const tower_defense::WeaponFire& getFire(int fireClass) const;

		// returns texture representing given weapon fire
		const sf::Texture &getTexture(int fireClass) const;

		//loads a weapon fire from (directory)(WEAPON_FIRES_LOCATION)name.xml
		//if wasn't already loaded
		tower_defense::WeaponFire* load(const std::string& directory, const std::string& name);

		// clears all fires from the manager
		void clear();
	private:
		std::map<std::string, int> fireIds;
		std::map<int, tower_defense::WeaponFire*> fires;

		int nextClass = 0;
	};
}

#endif