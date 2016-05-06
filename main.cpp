#define LOAD_TEST
// test of game loading
#define DISPLAY_TEST

#include <iostream>
#include "graphics/menu/Menu.h"


#if defined LOAD_TEST || defined DISPLAY_TEST

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

#ifndef DISPLAY_TEST
	std::string b;
	std::getline(std::cin, b);
#endif

#endif


    sf::RenderWindow window(sf::VideoMode(600, 600), "TowerDefense", sf::Style::None);

#if defined DISPLAY_TEST
	graphics::GameContent* c = nullptr;

	try {
		c = new graphics::GameContent(window);
	}
	catch (std::exception e) {
		std::cout << e.what() << std::endl;
		std::this_thread::sleep_for(std::chrono::seconds(1));
	}
	catch (...) {
		std::cout << "WTH?" << std::endl;
		std::this_thread::sleep_for(std::chrono::seconds(1));
	}


	while (window.isOpen()) {
		try {
			window.clear();

			c->refresh(window);

			window.display();

			std::this_thread::sleep_for(std::chrono::milliseconds(20));
		}
		catch (std::exception e) {
			std::cout << e.what() << std::endl;
			std::string b;
			std::getline(std::cin, b);
			return 0;
		}
		catch (...) {
			std::cout << "WTH?" << std::endl;
			std::string b;
			std::getline(std::cin, b);
			return 0;
		}
	}
	delete c;
#else
\
    Menu menu(window.getSize().x, window.getSize().y);

    while (window.isOpen()){
        sf::Event event;

        while (window.pollEvent(event)){
            switch (event.type){
                case sf::Event::KeyReleased:

                    // navigate between menu items

                    switch(event.key.code){
                        case sf::Keyboard::Up:
                            menu.moveUp();
                            break;
                        case sf::Keyboard::Down:
                            menu.moveDown();
                            break;


                        // pressing menu items

                        case sf::Keyboard::Return:
                            switch(menu.getPressedItem()){
                                case 0:
                                    std::cout << "Play button has been pressed" << std::endl;
                                    break;

                                case 1:
                                    std::cout << "Options button has been pressed" << std::endl;
                                    break;

                                case 2:
                                    window.close();
                                    break;

                            }

                    }
                    break;

                case sf::Event::Closed:
                    window.close();
                    break;
            }
        }

	    window.clear();

		menu.draw(window);

		window.display();
	}

#endif
#if defined LOAD_TEST || defined DISPLAY_TEST
	AppModel::getInstance().closeGame();
#endif
    return 0;
}
