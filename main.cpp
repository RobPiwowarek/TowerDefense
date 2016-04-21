#define LOAD_TEST
// test of game loading
#define DISPLAY_TEST

#include <iostream>
#include "graphics/menu/Menu.h"


#if defined LOAD_TEST || defined DISPLAY_TEST
#include "threading\AppModel.h"
#include "logic\Game.h"
#include "data\GameManager.h"
#include "data\MinionManager.h"
#include "graphics\TextureManager.h"
#ifdef DISPLAY_TEST
#include "graphics\GameDisplayer.h"
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
		g = AppModel::getInstance().getGame().get();
		gLocekd = true;

		std::cout << "Map size: " << g->getMap().getWidth() << std::endl;

		const tower_defense::Minion& m = AppModel::getInstance().getMinionManager().get()->getMinion(0);
		AppModel::getInstance().getMinionManager().release();

		std::cout << "Minion 0:" << std::endl;
		std::cout << "\tHealth: " << m.getHealth() << std::endl;
		std::cout << "\tReward:" << m.getReward() << std::endl;
		std::cout << "\tSize:" << m.getSize() << std::endl;
		AppModel::getInstance().getGame().release();
	}
	catch (std::exception e) {
		std::cout << e.what();
		if (gLocekd)
			AppModel::getInstance().getGame().release();
		return 0;
	}

	std::string b;
#ifndef DISPLAY_TEST
	std::getline(std::cin, b);
#endif

#endif


    sf::RenderWindow window(sf::VideoMode(600, 600), "TowerDefense");

#if defined DISPLAY_TEST
	graphics::GameDisplayer d(tower_defense::Point(0, 0));

	while (window.isOpen()) {
		try {
			window.clear();

			static sf::Event event;

			while (window.pollEvent(event)) {
				switch (event.type) {
				case sf::Event::Closed:
					window.close();
					break;
				case sf::Event::KeyPressed:
					switch (event.key.code) {
					case sf::Keyboard::PageUp:
						d.setPointsPerUnit(d.getPointsPerUnit() * 3 / 2);
						break;
					case sf::Keyboard::PageDown:
						d.setPointsPerUnit(d.getPointsPerUnit() * 2 / 3);
						break;
					case sf::Keyboard::Up:
						d.moveScreen(tower_defense::Point(0, -10.0 / d.getPointsPerUnit()));
						break;
					case sf::Keyboard::Down:
						d.moveScreen(tower_defense::Point(0, 10.0 / d.getPointsPerUnit()));
						break;
					case sf::Keyboard::Left:
						d.moveScreen(tower_defense::Point(-10.0 / d.getPointsPerUnit(), 0));
						break;
					case sf::Keyboard::Right:
						d.moveScreen(tower_defense::Point(10.0 / d.getPointsPerUnit(), 0));
						break;
					}
					break;
				}
			}

			d.refresh(window);

			window.display();
		}
		catch (std::exception e) {
			std::cout << e.what() << std::endl;
			static std::string buff;
			std::this_thread::sleep_for(std::chrono::seconds(1));
		}
		catch (...) {
			std::cout << "WTH?" << std::endl;
			static std::string buff;
			std::this_thread::sleep_for(std::chrono::seconds(1));
		}
	}
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
