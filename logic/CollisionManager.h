#ifndef TOWERDEFENSE_COLLISIONMANAGER_H
#define TOWERDEFENSE_COLLISIONMANAGER_H

namespace tower_defense {
	class CollisionManager;
}

#include <vector>
#include "Entity.h"
#include "Map.h"

namespace tower_defense {
    class CollisionManager {
        
	public:
		CollisionManager(tower_defense::Map map);
		bool checkCollision(tower_defense::Minion minion, tower_defense::Entity missile);
		

	private:
		tower_defense::Grid & grid;
		tower_defense::Map & map;
    };
}

#endif //TOWERDEFENSE_COLLISIONMANAGER_H
