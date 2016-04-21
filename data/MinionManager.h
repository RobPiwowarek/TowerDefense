#ifndef MINION_MANAGER_H
#define MINION_MANAGER_H

namespace data {
    class MinionManager;
}

#include "../logic/Minion.h"
#include <map>
#include "../include/SFML/Graphics.hpp"

namespace data {
    class MinionManager {
    public:
        const std::string MINION_LOCATION = "minions\\";

        ~MinionManager();

        // clears all minions from the manager
        void clear();

        // adds minion to the manager form file in (GAME_FILE_LOCATION)(MINION_LOCATION)name.xml
        // if wasn't already added to the manager
        // returns nullptr on failiure
        tower_defense::Minion *addMinion(const std::string &path, const std::string &name);

        // returns minion added with the given name
        const tower_defense::Minion &getMinion(const std::string &name) const;

        // returns minion added with the given class
        const tower_defense::Minion &getMinion(int minionClass) const;

        // returns texture associated with the given minion
        const sf::Texture &getTexture(int minionClass) const;

    private:
        std::map<std::string, int> minionClasses;
        std::map<int, tower_defense::Minion *> minions;
        std::map<int, std::string> textures;
        int nextClass = 0;

        tower_defense::Minion *load(const std::string &mDirectory, const std::string &name);
    };
}

#endif