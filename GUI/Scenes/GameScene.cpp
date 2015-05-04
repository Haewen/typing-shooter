#include <SFML/Graphics.hpp>
#include "../../Logic/GameLogic.h"
#include "../../GUI/EnemyGUI.h"
#include "../../GUI/MissileGUI.h"
#include "../../GUI/Scenes/Scene.cpp"
#include "../../GUI/Scenes/PauseScene.cpp"
#include "../../GUI/Scenes/GameOverScene.cpp"

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
        
        // Wave score text
        int currentWave = 0;
        int waveScoreAlpha = 0;
        sf::Font* f = new sf::Font();
        f->loadFromFile("Resources/Fonts/Ubuntu-Regular.ttf");
        sf::Text* waveScoreText = new sf::Text("Wave 234.\nScore 212312313",*f);
        sf::FloatRect textRect = waveScoreText->getLocalBounds();
        //waveScoreText->setOrigin(textRect.left + textRect.width/2.0f, textRect.top  + textRect.height/2.0f);
        waveScoreText->setPosition(sf::Vector2f(10, resolution.getY()-textRect.height-10));
        waveScoreText->setColor(sf::Color(255,255,255,waveScoreAlpha));
        waveScoreText->setCharacterSize(25);
        waveScoreText->setStyle(sf::Text::Style::Bold);
        
        //Event loop
        while (window.isOpen())
        {
            sf::Event event;
            switch (currentState)
            {
                case (GameState::Running):
                case (GameState::NewWave):
                    
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
                                window.capture().saveToFile("screenshot_temp.png");
                                currentState = GameState::Paused;
                                
                                int pauseSelection = static_cast<Scene*>(&pauseScene)->run(window);
                                if(pauseSelection == -1){
                                    currentState = GameState::Running;
                                    deltaClock.restart();
                                }else{
                                    return pauseSelection;
                                }
                                
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
                    
                    if(closestEnemy != NULL){
                        float distance = fmax(((50-closestEnemy->getPosition().distance(l.getPlayerPosition())) * 2) / 100,0);
                        redOverlay->setFillColor(sf::Color(255,0,0,75*distance));
                    }
                    
                    window.draw(player);
                    
                    l.update(deltaClock.getElapsedTime().asSeconds());
                    deltaClock.restart();
                    
                    if (l.isGameOver())
                    {
                        window.capture().saveToFile("screenshot_temp.png");
                        currentState = GameState::GameOver;
                    }
                    
                    if(currentState == GameState::NewWave){
                        if(waveScoreAlpha == 0){
                            currentWave++;
                            waveScoreText->setString("Wave " + std::to_string(currentWave) + ".\n" + "Score " + std::to_string(l.getScore()));
                            missiles.clear(); std::cout << l.getScore() << std::endl; l.nextWave(); getEnemies(enemies, l);
                            deltaClock.restart();
                        }
                        
                        if(waveScoreAlpha < 255){
                            waveScoreAlpha += 5;
                            waveScoreText->setColor(sf::Color(255,255,255,waveScoreAlpha));
                            window.draw(*waveScoreText);
                        }else{
                            waveScoreAlpha = 0;
                            currentState = GameState::Running;
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
