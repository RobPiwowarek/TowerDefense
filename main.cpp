#define LOAD_TEST
// test of game loading
#define DISPLAY_TEST
#define RUN_TEST

#include <iostream>
#include "graphics/menu/Menu.h"


#if defined LOAD_TEST || defined DISPLAY_TEST

#ifdef RUN_TEST
#include "threading\Refresher.h"
#endif

#include "threading/AppModel.h"
#include "logic/Game.h"
#include "data/GameManager.h"
#include "data/MinionManager.h"
#include "data/TurretManager.h"
#include "graphics/TextureManager.h"

#ifdef DISPLAY_TEST
#include "graphics/GameDisplayer.h"
#include "graphics/GameContent.h"
#include <thread>
#endif

#endif

int main(int argn, char** argv){
	for (int i = 0; i < argn; i++)
		std::cout << argv[i] << std::endl;

#if (defined LOAD_TEST || defined DISPLAY_TEST)
	tower_defense::Game* g = nullptr;
	bool gLocekd = false;
	try {

		std::string path = std::string(argv[0]).substr(0, std::string(argv[0]).find_last_of("\\/")) + "\\res\\game.xml";
		std::cout << "Loading " << path << std::endl;


		AppModel::getInstance().createGame(path);

		std::cout << "Game created\n";

		g = AppModel::getInstance().getGame().get();
		gLocekd = true;

		std::cout << "Map size: " << g->getMap().getWidth() << std::endl;

		const tower_defense::Minion& m = AppModel::getInstance().getMinionManager().get()->getMinion(0);
		AppModel::getInstance().getMinionManager().release();

		std::cout << "Minion 0:" << std::endl;
		std::cout << "\tHealth: " << m.getHealth() << std::endl;
		std::cout << "\tReward:" << m.getReward() << std::endl;
		std::cout << "\tSize:" << m.getSize() << std::endl;

		std::cout << "Items:" << std::endl;
		for (auto i = g->getMap().getItems().begin(); i != g->getMap().getItems().end(); i++)
			std::cout << "[" << (*i)->getLocation().getX() << ", " << (*i)->getLocation().getY() << "]" << std::endl;

		AppModel::getInstance().getGame().release();

		std::vector<std::pair<int, std::pair<std::string, int> > > turrets;
		AppModel::getInstance().getTurretManager().get()->getTurrets(turrets);
		AppModel::getInstance().getTurretManager().release();

		std::cout << "Turrets:" << std::endl;
		for (int i = 0; i < turrets.size(); i++) {
			std::cout << "\t" << turrets[i].first << ": " << turrets[i].second.first << ", $:" << turrets[i].second.second << std::endl;
		}


	}
	catch (std::exception e) {
		std::cout << e.what();
		if (gLocekd)
			AppModel::getInstance().getGame().release();
		std::string b;
		std::getline(std::cin, b);
		return 0;
	}
	catch (int i) {
		std::cout << "Error:" << i;
		return 0;
	}
	try {
		AppModel::getInstance().runWindow();
	}
	catch (std::exception e) {
		std::cout << "DispEsc: " << e.what();
	}
#ifndef DISPLAY_TEST
	std::string b;
	std::getline(std::cin, b);
#endif

#endif
}
