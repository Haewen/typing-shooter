#include "Scene.cpp"
#include "../../Logic/Position.h"
#include <iostream>

#ifndef MAIN_MENU
#define MAIN_MENU
class MainMenu : public Scene
{
	int run(sf::RenderWindow &window)
	{
		Position resolution(window.getSize().x, window.getSize().y);

		//Setting background
		sf::Sprite *background = new sf::Sprite();
		sf::Texture *backgroundTexture = new sf::Texture;
		backgroundTexture->loadFromFile("Resources/Backgrounds/stars.png");
		backgroundTexture->setRepeated(true);
		background->setTexture(*backgroundTexture);
		background->setTextureRect(sf::IntRect(0, 0, resolution.getX(), resolution.getY()));
		
		//Loading logo
		sf::RectangleShape *logo = new sf::RectangleShape();
		sf::Texture *logoTexture = new sf::Texture;
		logoTexture->loadFromFile("Resources/Menu/logo.png");
		logoTexture->setSmooth(true);
		logo->setTexture(logoTexture);
		logo->setSize(sf::Vector2f(696/2, 260/2));
		logo->setOrigin(sf::Vector2f(logo->getSize().x / 2, logo->getSize().y / 2));
		logo->setPosition(sf::Vector2f(resolution.getX()/2,resolution.getY()/4));

		//Loading Menu Background
		sf::RectangleShape menuBackground;
		sf::Texture *menuTexture = new sf::Texture;
		menuTexture->loadFromFile("Resources/Backgrounds/menu_background.png");
		menuBackground.setTexture(menuTexture);
		menuBackground.setSize(sf::Vector2f(400, 300));
		menuBackground.setOrigin(sf::Vector2f(menuBackground.getSize().x / 2, menuBackground.getSize().y / 2));
		menuBackground.setPosition(sf::Vector2f(resolution.getX() / 2, resolution.getY() / 7*4.5));

		//New Game Button
		/*sf::Font* f = new sf::Font();
		f->loadFromFile("Resources/BebasNeue.ttf");
		sf::Text newGame;
		newGame.setFont(*f);
		newGame.setString("New Game");
		newGame.setColor(sf::Color::White);
		newGame.setOrigin((newGame.getLocalBounds().width / 2),
			(newGame.getLocalBounds().height / 2));
		newGame.setPosition(sf::Vector2f(resolution.getX()/2,resolution.getY()/2));
		newGame.setCharacterSize(50);*/

		//Loading newGameButton
		sf::RectangleShape *newGame = new sf::RectangleShape();
		sf::Texture *newGameTexture = new sf::Texture;
		newGameTexture->loadFromFile("Resources/Menu/newgame.png");
		newGameTexture->setSmooth(true);

		sf::Texture *newGameTextureS = new sf::Texture;
		newGameTextureS->loadFromFile("Resources/Menu/newgameselected.png");
		newGameTextureS->setSmooth(true);


		newGame->setTexture(newGameTexture);
		newGame->setSize(sf::Vector2f(500 / 2, 100 / 2));
		newGame->setOrigin(sf::Vector2f(newGame->getSize().x / 2, newGame->getSize().y / 2));
		newGame->setPosition(sf::Vector2f(resolution.getX() / 2, resolution.getY() / 2));

		while (window.isOpen())
		{
			sf::Event event;
			while (window.pollEvent(event))
			{
				if (event.type == sf::Event::Closed)
					window.close();

				sf::Vector2i mousePosition = sf::Mouse::getPosition(window);
				if (newGame->getGlobalBounds().contains(mousePosition.x, mousePosition.y))
				{
					newGame->setTexture(newGameTextureS);
					if (sf::Mouse::isButtonPressed(sf::Mouse::Left))
					{
						return 1;
					}
				}
				else newGame->setTexture(newGameTexture);
			}

			window.clear();
			window.draw(*background);
			window.draw(*logo);
			window.draw(menuBackground);
			window.draw(*newGame);
			window.display();

		}

		return -1;
	}

};
#endif