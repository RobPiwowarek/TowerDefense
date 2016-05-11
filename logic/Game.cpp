#include "Game.h"
#include "../data/MinionWaveManager.h"


#include <iostream>

tower_defense::Game::Game(Map *m, Player *p) : map(m), player(p) {
    this->curWave = 0;
	std::cout << "w";
	this->wave = new MinionWave(AppModel::getInstance().getMinionWaveManager().get()->get(this->curWave));
	std::cout << "w\n";
	AppModel::getInstance().getMinionWaveManager().release();
}

tower_defense::Map &tower_defense::Game::getMap() {
    return *this->map;
}

tower_defense::MinionWave &tower_defense::Game::getCurrentWave() {
    return *this->wave;
}

tower_defense::Player &tower_defense::Game::getPlayer() {
    return *this->player;
}

void tower_defense::Game::refresh() {
	if (this->wave != nullptr)
	{

		Minion* newMinion = this->wave->refresh();

		if (newMinion != nullptr) {
			Point location;

			switch (rand() % 4) {
			case 1: //E
				location.setX(this->map->getWidth() - 0.001);
			case 3: //W
				location.setY(((rand() * 1000) % ((int)this->map->getHeight() * 1000)) * 0.001);
				break;
			case 2: //S
				location.setY(this->map->getHeight() - 0.001);
			case 0: //N
				location.setX(((rand() * 1000) % ((int)this->map->getWidth() * 1000)) * 0.001);
				break;
			}
			std::cout << "adding minion: (" << location.getX() << ", " << location.getY() << ")" << std::endl;
			this->map->addMinion(new Minion(*newMinion, location));
		}

		if (this->wave->finished()) {
			std::cout << "Wave";
			delete this->wave;
			data::MinionWaveManager* manager = AppModel::getInstance().getMinionWaveManager().get();

			if (++this->curWave == manager->count())
				this->wave = nullptr;
			else
				this->wave = new MinionWave(manager->get(this->curWave));

			AppModel::getInstance().getMinionWaveManager().release();
			std::cout << " finished\n";
		}
	}


    //this->map->refresh(*this);
}

tower_defense::Game::~Game() {
    delete this->player, this->map;
}