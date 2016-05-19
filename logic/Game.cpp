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

void tower_defense::Game::refreshWave() {
	if (this->wave != nullptr) {

		Minion* newMinion = this->wave->refresh();

		if (newMinion != nullptr) {
			Point location;

			switch (rand() % 4) {
			case 1: //E
				location.setX(this->map->getWidth() - 0.001);
			case 3: //W
				location.setY((rand() % ((int)this->map->getHeight() * 100)) * 0.01);
				break;
			case 2: //S
				location.setY(this->map->getHeight() - 0.001);
			case 0: //N
				location.setX((rand() % ((int)this->map->getWidth() * 100)) * 0.01);
				break;
			}
			std::cout << "adding minion: (" << location.getX() << ", " << location.getY() << ")" << std::endl;
			this->map->addMinion(new Minion(*newMinion, location));
		}

		if (this->wave->finished()) {
			delete this->wave;
			data::MinionWaveManager* manager = AppModel::getInstance().getMinionWaveManager().get();

			if (++this->curWave == manager->count())
				this->wave = nullptr;
			else
				this->wave = new MinionWave(manager->get(this->curWave));

			AppModel::getInstance().getMinionWaveManager().release();
		}
	}
}

void tower_defense::Game::refresh() {
	this->refreshWave();
    this->map->refresh(*this);
	if (player->getNItems() == 0)
		AppModel::getInstance().setState(AppModel::Defeat);
	else if (this->wave == nullptr)
		if (this->getMap().getMinions().empty())
			AppModel::getInstance().setState(AppModel::Victory);


	//std::cout << "Game state: " << AppModel::getInstance().getState() << " items: " << player->getNItems() << std::endl;
}

tower_defense::Game::~Game() {
    delete this->player, this->map;
}
void tower_defense::Game::addTurret(const Turret* base, const Point& p, const int cost) {
	if (this->player->getMoney() < cost) return;
	if (this->map->canPlaceTurret(p, *base)) {
		this->player->setMoney(this->player->getMoney() - cost);
		this->map->addTurret(new Turret(*base, p));
	}
}