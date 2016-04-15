#include <iostream>
#include "graphics/menu/Menu.h"

int main(void){
    sf::RenderWindow window(sf::VideoMode(600, 600), "TowerDefense");


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

    return 0;
}
