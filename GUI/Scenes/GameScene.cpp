#include <SFML/Graphics.hpp>
#include "../../Logic/GameLogic.h"
#include "../../GUI/EnemyGUI.h"
#include "../../GUI/MissileGUI.h"
#include "../../GUI/Scenes/Scene.cpp"

#include <iostream>


#ifndef GAMESCENE
#define GAMESCENE

enum GameState
{
	Running,Paused,NewWave,GameOver
};


class GameScene : public Scene
{
public:
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

		//window.setFramerateLimit(60);
		//window.setVerticalSyncEnabled(true);
		window.setKeyRepeatEnabled(false);

		//Timer to measure deltaTime for framerate independency
		sf::Clock deltaClock;
		//Creating gamelogic
		GameLogic l = GameLogic();
		//Starting new game
		l.newGame();
		//Enemy bodies
		std::vector<EnemyGUI> enemies;
		getEnemies(enemies, l);
		std::vector<MissileGUI> missiles;

		sf::RectangleShape player;
		sf::Texture *playerTexture = new sf::Texture;
		playerTexture->loadFromFile("Resources/Sprites/player.png");
		player.setTexture(playerTexture);
		player.setSize(sf::Vector2f(50, 50));
		player.setOrigin(sf::Vector2f(25, 25));

		GameState currentState = GameState::Running;

		//Event loop
		while (window.isOpen())
		{
			sf::Event event;
			window.clear();
			switch (currentState)
			{
				case (GameState::Running):

					while (window.pollEvent(event))
					{
						if (event.type == sf::Event::Closed)
							window.close();

						if (event.type == sf::Event::TextEntered)
						{
							if (event.text.unicode < 128)
							{
								char c = tolower((char)event.text.unicode);
								l.shoot(c);
							}
						}

						if (event.type == sf::Event::KeyPressed)
						{
							if (event.key.code == sf::Keyboard::Escape)
							{
								currentState = GameState::Paused;
							}
						}
					}

					player.setPosition(sf::Vector2f(l.getPlayerPosition().getX()*resolution.getX() *0.01f, l.getPlayerPosition().getY()*resolution.getY() *0.01f));

					//Starts wave if previous one is defeated
					if (l.isWaveOver()){ missiles.clear(); std::cout << l.getScore() << std::endl; l.nextWave(); getEnemies(enemies, l); }
					window.draw(*background);

					//Draws enemies still alive
					for (int i = 0; i < enemies.size(); i++)
					{
						if (!l.getEnemies()[i].isExploded())
						{
							enemies[i].setPosition(sf::Vector2f(l.getEnemies()[i].getPosition().getX()*resolution.getX() *0.01f,
								l.getEnemies()[i].getPosition().getY()* resolution.getY() *0.01f));
							if (&l.getEnemies()[i] == &l.getTarget())
							{
								enemies[i].setAsTarget();
							}
							enemies[i].updateText();
							window.draw(enemies[i]);
						}
					}

					for (int i = missiles.size(); i < l.getMissiles().size(); i++)
					{
						missiles.push_back(MissileGUI(l.getMissiles()[i]));
					}

					for (int i = 0; i < l.getMissiles().size(); i++)
					{
						if (!l.getMissiles()[i].isDead())
						{
							missiles[i].setPosition(sf::Vector2f(l.getMissiles()[i].getPosition().getX()*resolution.getX()*0.01f,
								l.getMissiles()[i].getPosition().getY()* resolution.getY() *0.01f));
							window.draw(missiles[i]);
						}
					}


					window.draw(player);

					l.update(deltaClock.getElapsedTime().asSeconds());
					deltaClock.restart();

					if (l.isGameOver())
					{
						return 0;
					}

					break;

				case (GameState::NewWave) :
					break;
				case (GameState::GameOver) :
					break;
				case (GameState::Paused) :
					while (window.pollEvent(event))
					{
						if (event.type == sf::Event::Closed)
							window.close();

						if (event.type == sf::Event::KeyPressed)
						{
							if (event.key.code == sf::Keyboard::Escape)
							{
								currentState = GameState::Running;
								deltaClock.restart();
							}
						}
					}
					break;
				}
				window.display();
		}

		return -1;
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

};

#endif
