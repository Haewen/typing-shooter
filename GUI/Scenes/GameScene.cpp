/**
Game Scene

@authors Dániel Eke, Benjamin Ferenc Hajas
*/

#include <SFML/Graphics.hpp>
#include "../../Logic/GameLogic.h"
#include "../../GUI/EnemyGUI.h"
#include "../../GUI/MissileGUI.h"
#include "../../GUI/Scenes/Scene.cpp"
#include "../../GUI/Scenes/PauseScene.cpp"
#include "../../GUI/Scenes/GameOverScene.cpp"
#include <SFML/Audio.hpp>

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
        
        //Background overlay
        sf::RectangleShape *redOverlay = new sf::RectangleShape();
        redOverlay->setSize(sf::Vector2f(resolution.getX(), resolution.getY()));
        redOverlay->setFillColor(sf::Color(0,0,0,0));
        redOverlay->setPosition(0, 0);
        
      
        //window.setFramerateLimit(60);
        //window.setVerticalSyncEnabled(true);
        window.setKeyRepeatEnabled(false);
        
        //Timer to measure deltaTime for framerate independency
        sf::Clock deltaClock;
        float deltaTime = 0;
        //Creating gamelogic
        GameLogic l = GameLogic();
        //Starting new game
        l.newGame();
        //Enemy bodies
        std::vector<EnemyGUI> enemies;
        getEnemies(enemies, l);
        std::vector<MissileGUI> missiles;
        Enemy *closestEnemy;
        PauseScene pauseScene;
        GameOverScene gameOverScene;
        
        sf::RectangleShape player;
        sf::Texture *playerTexture = new sf::Texture;
        playerTexture->loadFromFile("Resources/Sprites/player.png");
        player.setTexture(playerTexture);
        player.setSize(sf::Vector2f(50, 50));
        player.setOrigin(sf::Vector2f(25, 25));
        
        GameState currentState = GameState::Running;
        
        // Wave and score display
        int currentWave = 0;
        float waveAlpha = 0;
        sf::Font* f = new sf::Font();
        f->loadFromFile("Resources/Fonts/Ubuntu-Regular.ttf");
        
        sf::Text* scoreText = new sf::Text("Score 212312313",*f);
        scoreText->setPosition(sf::Vector2f(10, resolution.getY()-scoreText->getLocalBounds().height-10));
        scoreText->setColor(sf::Color::White);
        scoreText->setCharacterSize(25);
        scoreText->setStyle(sf::Text::Style::Bold);
        
        sf::Text* waveText = new sf::Text("Wave 9999",*f);
        sf::FloatRect waveRect = waveText->getLocalBounds();
        waveText->setOrigin(waveRect.left + waveRect.width/2.0f, waveRect.top  + waveRect.height/2.0f);
        waveText->setPosition(sf::Vector2f(resolution.getX()/2, resolution.getY()/2));
        waveText->setColor(sf::Color(255,255,255,waveAlpha));
        waveText->setCharacterSize(30);
        waveText->setStyle(sf::Text::Style::Bold);

		//Sounds
		sf::SoundBuffer buffer;
		sf::Sound sound;

		//loading background music
		sf::Music music;
		if (!music.openFromFile("Resources/Sounds/bg.ogg")) std::cerr << "oops\n";
		music.setVolume(100);
		music.setLoop(true);

		if (window.isOpen()) music.play();

        //Event loop
        while (window.isOpen())
        {
            sf::Event event;
            switch (currentState)
            {
                case (GameState::Running):
                case (GameState::NewWave):
                    deltaTime = deltaClock.getElapsedTime().asSeconds();
                    while (window.pollEvent(event))
                    {
                        if (event.type == sf::Event::Closed)
                            window.close();
                        
                        if (event.type == sf::Event::TextEntered)
                        {
                            if (event.text.unicode < 128)
                            {
                                char c = tolower((char)event.text.unicode);
								if (l.shoot(c))
								{
									//Shooting sound
									buffer.loadFromFile("Resources/Sounds/shot.wav");
									sound.setBuffer(buffer);
									sound.setVolume(5);
									sound.play();
								}
                            }
                        }
                        
                        if (event.type == sf::Event::KeyPressed)
                        {
                            if (event.key.code == sf::Keyboard::Escape)
                            {
								music.pause();
                                window.capture().saveToFile("screenshot_temp.png");
                                currentState = GameState::Paused;
                                
                                int pauseSelection = static_cast<Scene*>(&pauseScene)->run(window);
                                if(pauseSelection == -1){
									music.play();
                                    currentState = GameState::Running;
                                    deltaClock.restart();
                                }else{
                                    return pauseSelection;
                                }
                                
							}
							else {
								//"Mistype" sound
								buffer.loadFromFile("Resources/Sounds/ooa.wav");
								sound.setBuffer(buffer);
								sound.setVolume(5);
								sound.play();
							}
						}
						
                    }
                    
                    window.clear();
                    player.setPosition(sf::Vector2f(l.getPlayerPosition().getX()*resolution.getX() *0.01f, l.getPlayerPosition().getY()*resolution.getY() *0.01f));
                    
                    //Starts wave if previous one is defeated
                    if (l.isWaveOver()){
                        currentState = GameState::NewWave;
                    }
                    window.draw(*background);
                    window.draw(*redOverlay);
                    
                    closestEnemy = NULL;
                    //Draws enemies still alive
                    for (int i = 0; i < enemies.size(); i++)
                    {
                        if (!l.getEnemies()[i].isExploded())
                        {
                            if(closestEnemy == NULL){
                                // The closest is always the first not exploded enemy
                                closestEnemy = &l.getEnemies()[i];
                            }
                            
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
                    
                    // Proxitimy indicator, based on the closest enemy
                    // If its within 50% distance, fade in the red overlay
                    if(closestEnemy != NULL){
                        float distance = fmax(((50-closestEnemy->getPosition().distance(l.getPlayerPosition())) * 2) / 100,0);
                        redOverlay->setFillColor(sf::Color(255,0,0,75*distance));
                    }
                    
                    window.draw(player);
                    
                    scoreText->setString("Score " + std::to_string(l.getScore()));
                    window.draw(*scoreText);
                    
                    l.update(deltaTime);
                    deltaClock.restart();
                    
                    if (l.isGameOver())
                    {
						music.stop();
						buffer.loadFromFile("Resources/Sounds/go.wav");
						sound.setBuffer(buffer);
						sound.setVolume(100);
						sound.play();
                        window.capture().saveToFile("screenshot_temp.png");
                        currentState = GameState::GameOver;
                    }
                    

                    // If the last wave ended, increment the current wave and fade in the indicator
                    if(currentState == GameState::NewWave){
                        if(waveAlpha <= 0){
							//next wave sound
							if (currentWave > 0)
							{
								buffer.loadFromFile("Resources/Sounds/wave.wav");
								sound.setBuffer(buffer);
								sound.setVolume(90);
								sound.play();
							}

                            currentWave++;
                            waveText->setString("Wave " + std::to_string(currentWave));
                            missiles.clear(); l.nextWave(); getEnemies(enemies, l);
                            //deltaClock.restart();
                            waveAlpha = 0.1;
                        }
                        
                        waveAlpha += deltaTime * 200.0;
                        waveText->setColor(sf::Color(255,255,255,waveAlpha));
                        window.draw(*waveText);

                        if(waveAlpha >= 255){
                            currentState = GameState::Running;
                        }
                    } else {
                        // If the indicator is visible, fade it out
                        if(waveAlpha >= 0){
                            waveAlpha -= deltaTime * 200.0;
                            waveText->setColor(sf::Color(255,255,255,fmax(0,waveAlpha)));
                            window.draw(*waveText);
                        }
                    }
                    
                    break;
                case (GameState::GameOver) :
                    gameOverScene.score = l.getScore();
                    return static_cast<Scene*>(&gameOverScene)->run(window);
                    break;
                case (GameState::Paused) :
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
