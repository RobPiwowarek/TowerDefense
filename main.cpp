#include <iostream>
#include "graphics/menu/Menu.h"

#define LOAD_TEST
// test of game loading

#ifdef LOAD_TEST

#include "threading\AppModel.h"
#include "logic\Game.h"
#include "data\GameManager.h"
#include "data\MinionManager.h"
#include "graphics\TextureManager.h"

#endif

int main(int argn, char **argv) {
    for (int i = 0; i < argn; i++)
        std::cout << argv[i] << std::endl;

#ifdef LOAD_TEST
    tower_defense::Game *g = nullptr;
    try {

        std::string path = std::string(argv[0]).substr(0, std::string(argv[0]).find_last_of("\\/")) + "\\res\\game.xml";
        std::cout << "Loading " << path << std::endl;


        g = AppModel::getInstance().getGameManager().get()->load(path);
        std::cout << "Map size: " << g->getMap().getWidth() << std::endl;

        const tower_defense::Minion &m = AppModel::getInstance().getMinionManager().get()->getMinion(0);

        std::cout << "Minion 0:" << std::endl;
        std::cout << "\tHealth: " << m.getHealth() << std::endl;
        std::cout << "\tReward:" << m.getReward() << std::endl;
        std::cout << "\tSize:" << m.getSize() << std::endl;
    }
    catch (std::exception e) {
        std::cout << e.what();
    }
    std::string b;
    std::getline(std::cin, b);

    delete g;

#endif


    sf::RenderWindow window(sf::VideoMode(600, 600), "TowerDefense");


    Menu menu(window.getSize().x, window.getSize().y);

    while (window.isOpen()) {
        sf::Event event;

        while (window.pollEvent(event)) {
            switch (event.type) {
                case sf::Event::KeyReleased:

                    // navigate between menu items

                    switch (event.key.code) {
                        case sf::Keyboard::Up:
                            menu.moveUp();
                            break;
                        case sf::Keyboard::Down:
                            menu.moveDown();
                            break;


                            // pressing menu items

                        case sf::Keyboard::Return:
                            switch (menu.getPressedItem()) {
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
    return 0;
}
