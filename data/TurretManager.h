#ifndef TURRET_MANAGER_H
#define TURRET_MANAGER_H

namespace Data {
	class TurretManager;
}

#include <string>
#include <map>

#include "../include/SFML/Graphics.hpp"
#include "../include/pugixml/pugixml.hpp"

#include "../logic/Turret.h"
#include "../logic/Weapon.h"

namespace data {
	class TurretManager {
	public:
		const std::string TURRET_LOCATION = "turrets\\";
		const std::string WEAPON_FIRES_LOCATION = "fires\\";

		~TurretManager();

		// clears all turrets from the manager
		void clear();

		// adds turret to the manager from file in (GAME_FILE_LOCATION)(TURRRET_LOCATION)file.xml
		// if wasn't already added to the manager
		// returns nullptr on failiure
		tower_defense::Turret *addTurret(const std::string &path, const std::string &file);

		// returns turret added with the given class
		const tower_defense::Turret &getTurret(int turretClass) const;

		// returns texture associated with the given turret
		const sf::Texture &getTexture(int turretClass) const;

		// returns texture associated with the given weapon fire
		const sf::Texture &getWeaponFireTexture(int weaponFireClass) const;

		// returns name of the given turret
		const std::string &getName(int turretClass) const;

	private:
		std::map<int, tower_defense::Turret *> turrets;
		std::map<int, std::string> names;
		std::map<int, tower_defense::WeaponFire *> weaponFires;
		std::map<int, WeaponFireList*> weaponFireLists;

		int nextClass = 0;
		int nextWeaponFireClass = 0;

		std::pair<tower_defense::Turret*, std::string> load(const std::string &directory, const std::string &file);
		tower_defense::Weapon* load(const pugi::xml_node& weaponNode, const std::string &directory, int turretObjClass);
		tower_defense::WeaponFire* loadWeaponFire(const pugi::xml_node& weaponFireNode, const std::string &directory);
	};
}

#endif