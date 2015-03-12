#include <SFML/Graphics.hpp>
#include "Logic/GameLogic.h"
#include "./GUI/EnemyGUI.h"
#include <iostream>


void getEnemies(std::vector<EnemyGUI> &enemies, GameLogic &l);
int main()
{
	sf::RenderWindow window(sf::VideoMode(800, 600), "Typing Shooter");
	sf::Clock deltaClock;
	GameLogic l = GameLogic(Position(800, 600));

	l.newGame();
	std::vector<EnemyGUI> enemies;
	getEnemies(enemies, l);

	sf::RectangleShape player;
	player.setSize(sf::Vector2f(10, 10));
	player.setPosition(sf::Vector2f(l.getPlayerPosition().getX(), l.getPlayerPosition().getY()));
	player.setOrigin(sf::Vector2f(5, 5));
	player.setFillColor(sf::Color::Green);

	window.setFramerateLimit(60);
	window.setVerticalSyncEnabled(false);
	window.setKeyRepeatEnabled(false);

	while (window.isOpen() && !l.isGameOver())
	{
		sf::Event event;
		while (window.pollEvent(event))
		{
			if (event.type == sf::Event::Closed)
				window.close();

			/*if (event.type == sf::Event::Resized)
				window.setView(sf::View(sf::FloatRect(0,0,window.getSize().x,window.getSize().y)));*/


			if (event.type == sf::Event::TextEntered)
			{
				if (event.text.unicode < 128){
					char c = tolower((char)event.text.unicode);
					l.shoot(c);
					std::cout << c;
				}
			}

		}

		if (l.isWaveOver()){ l.nextWave(); getEnemies(enemies, l); }

		window.clear();
		for (int i = 0; i < enemies.size(); i++)
		{
			if (!l.getEnemies()[i].isDead()){
				enemies[i].setPosition(sf::Vector2f(l.getEnemies()[i].getPosition().getX(), l.getEnemies()[i].getPosition().getY()));
				window.draw(enemies[i]);
			}
		}
		window.draw(player);
		window.display();
		l.update(deltaClock.getElapsedTime().asSeconds());
		deltaClock.restart();
	}

	return 0;
}

void getEnemies(std::vector<EnemyGUI> &enemies, GameLogic &l)
{
	enemies.clear();
	for (int i = 0; i < l.getEnemyCount(); i++)
	{
		EnemyGUI e(l.getEnemies()[i]);
		enemies.push_back(e);
	}
}