#ifndef LABEL_H
#define LABEL_H

#include "../include/SFML/Graphics.hpp"
#include <string>

namespace graphics {
	class Label {
	public:
		Label(const sf::Vector2f &size, const sf::Vector2f &location, const sf::Texture* background);
		Label(const sf::Vector2f &size, const sf::Vector2f & location, const sf::Texture* background,
			const sf::Texture* icon);
		Label(const sf::Vector2f &size, const sf::Vector2f &location, const sf::Texture* background,
			const std::string& descr);
		Label(const sf::Vector2f &size, const sf::Vector2f &location, const sf::Texture* background,
			const sf::Texture* icon, const std::string& descr);


		// returns item size
		sf::Vector2f& getSize();
		// sets item size
		void setSize(const sf::Vector2f& size);
		// returns item location
		sf::Vector2f& getLocation();
		// sets item location
		void setLocation(const sf::Vector2f& location);

		// returns color of the displayed text
		void setForeColor(const sf::Color &c);
		// returns color of the displayed text
		sf::Color& getForeColor();

		// sets size of the font
		void setFontSize(int size);
		// returns size of the font
		int getFontSize();

		void display(sf::RenderWindow& window, std::string text);
	private:
		sf::RectangleShape background;
		const sf::Texture* icon = nullptr;

		sf::Color foreColor = sf::Color::Black;

		sf::Vector2f size;
		sf::Vector2f location;

		std::string descr;

		int fontSize = 30;
	};
}

#endif