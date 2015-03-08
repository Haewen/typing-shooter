#include <SFML/Graphics.hpp>
#include "GameLogic.h"

int main()
{
/*	sf::RenderWindow window(sf::VideoMode(200, 200), "SFML works!");
	sf::CircleShape shape(100.f);
	shape.setFillColor(sf::Color::Green);

	while (window.isOpen())
	{
		sf::Event event;
		while (window.pollEvent(event))
		{
			if (event.type == sf::Event::Closed)
				window.close();
		}

		window.clear();
		window.draw(shape);
		window.display();
	}
	*/
	sf::RenderWindow window(sf::VideoMode(800,600), "Typing Shooter");
	sf::Clock deltaClock;
	GameLogic l = GameLogic(Position(800, 600));
	l.newGame();
	std::vector<sf::RectangleShape> enemies;
	for (int i = 0; i < l.getEnemyCount(); i++)
	{
		sf::RectangleShape rect;
		rect.setSize(sf::Vector2f(10,10));
		rect.setFillColor(sf::Color::Red);
		rect.setOrigin(sf::Vector2f(5, 5));
		enemies.push_back(rect);
	}
	sf::RectangleShape player;
	player.setSize(sf::Vector2f(10, 10));
	player.setPosition(sf::Vector2f(l.getPlayerPosition().getX(),l.getPlayerPosition().getY()));
	player.setOrigin(sf::Vector2f(5, 5));
	player.setFillColor(sf::Color::Green);
	window.setFramerateLimit(60);
	int a = 0;
	while (window.isOpen())
	{
		a++;
		sf::Event event;
		while (window.pollEvent(event))
		{
			if (event.type == sf::Event::Closed)
				window.close();
		}

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