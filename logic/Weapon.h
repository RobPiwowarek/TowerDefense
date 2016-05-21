#ifndef WEAPON_H
#define WEAPON_H

#include <list>

namespace tower_defense {
    class Weapon;
}

#include "Minion.h"
#include "Turret.h"
#include "WeaponFire.h"
#include "Map.h"

typedef double angleModifier;

typedef std::list<std::pair<int, std::pair<tower_defense::WeaponFire *, angleModifier> > > WeaponFireList;

namespace tower_defense {

    /// class for objects that represent turret's weapons
    class Weapon {
    public:
        /// creates an instance of Weapon object
        /// using given values
        /// weaponFireList is list of weapon fires,
        /// sorted by fire time in weapon cycle
        /// highest time must be lower than fireRate
        Weapon(const double range, const int fireRate,
               const WeaponFireList *const weaponFireList);

        /// creates an exact copy of base
        /// with given parent
        Weapon(const Weapon &base, const Turret *const parent);

        /// returns weapon's maximum range
        double getRange() const;

        /// returns firing rate of weapon
        int getFireRate() const;

        /// returns time left to reload a weapon
        int getReloading() const;

        /// returns weapon's type
        int getClass() const;

        /// refreshes weapon
        void refresh(bool beginSequence, Map* m);

    private:
        const WeaponFireList *fireList;
        WeaponFireList::const_iterator cur;

        double range;
        int fireRate;
        int reloading;
        const Turret *parent;
    };

}

#endif