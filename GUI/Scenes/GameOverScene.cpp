/**
Game Over Scene

@authors Dániel Eke, Benjamin Ferenc Hajas
*/
#include "Scene.cpp"
#include "../../Logic/Position.h"
#include "../../Logic/ScoreLoader.h"
#include <vector>
#include <iostream>

#ifndef GAME_OVER_SCENE
#define GAME_OVER_SCENE
class GameOverScene : public Scene
{
public:
    int score = 0;
private:
    int run(sf::RenderWindow &window)
    {
        Position resolution(window.getSize().x, window.getSize().y);
        
        //Setting background
        sf::Shader backgroundShader;
        sf::Sprite *background = new sf::Sprite();
        sf::Texture *backgroundTexture = new sf::Texture;
        sf::Image *backgroundImage = new sf::Image;
        backgroundImage->loadFromFile("screenshot_temp.png");
        backgroundTexture->loadFromImage(*backgroundImage);
        backgroundTexture->setRepeated(true);
        backgroundShader.loadFromFile("Resources/Shaders/blur.frag", sf::Shader::Fragment);
        backgroundShader.setParameter("texture", sf::Shader::CurrentTexture);
        backgroundShader.setParameter("blur_radius", 0.001);
        background->setColor(sf::Color(255,255,255,200));
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
        
        //Loading player score
        sf::Font* f = new sf::Font();
        f->loadFromFile("Resources/Fonts/Ubuntu-Regular.ttf");
        sf::Text* scoreText = new sf::Text("Final score: " + std::to_string(score),*f);
        sf::FloatRect textRect = scoreText->getLocalBounds();
        scoreText->setOrigin(textRect.left + textRect.width/2.0f, textRect.top  + textRect.height/2.0f);
        scoreText->setPosition(sf::Vector2f(resolution.getX() / 2, resolution.getY() / 2));
        scoreText->setColor(sf::Color::White);
        scoreText->setCharacterSize(25);
        scoreText->setStyle(sf::Text::Style::Bold);
        
        //Player name handling
        std::string playerName;
        sf::Text* playerNameText = new sf::Text("Enter your name",*f);
        sf::FloatRect nameRect = playerNameText->getLocalBounds();
        playerNameText->setOrigin(nameRect.left + nameRect.width/2.0f, nameRect.top  + nameRect.height/2.0f);
        playerNameText->setPosition(sf::Vector2f(resolution.getX() / 2, resolution.getY() / 2 + buttonSpacing));
        playerNameText->setColor(sf::Color::White);
        playerNameText->setCharacterSize(25);
        playerNameText->setStyle(sf::Text::Style::Bold);
        
        
        //Loading mainmenuButton
        sf::RectangleShape *mainMenuButton = new sf::RectangleShape();
        sf::Texture *mainMenuTexture = new sf::Texture;
        mainMenuTexture->loadFromFile("Resources/Menu/mainmenu_button.png");
        mainMenuTexture->setSmooth(true);
        
        sf::Texture *mainMenuTextureS = new sf::Texture;
        mainMenuTextureS->loadFromFile("Resources/Menu/mainmenu_button_selected.png");
        mainMenuTextureS->setSmooth(true);
        
        mainMenuButton->setTexture(mainMenuTexture);
        mainMenuButton->setSize(sf::Vector2f(500 / 2, 100 / 2));
        mainMenuButton->setOrigin(sf::Vector2f(mainMenuButton->getSize().x / 2, mainMenuButton->getSize().y / 2));
        mainMenuButton->setPosition(sf::Vector2f(resolution.getX() / 2, resolution.getY() / 2 + buttonSpacing * 2));
        
        //Score saving logic
        ScoreLoader scoreLoader;
        
        while (window.isOpen())
        {
            sf::Event event;
            while (window.pollEvent(event))
            {
                if (event.type == sf::Event::Closed)
                    window.close();
                
                if (event.type == sf::Event::KeyPressed)
                {
                    if (event.key.code == sf::Keyboard::Escape)
                    {
                        return -1;
                    }
                }
                
                sf::Vector2i mousePosition = sf::Mouse::getPosition(window);
                if (mainMenuButton->getGlobalBounds().contains(mousePosition.x, mousePosition.y))
                {
					hoverSound();
                    mainMenuButton->setTexture(mainMenuTextureS);
                    if(event.type == sf::Event::MouseButtonReleased)
                    {
                        if(playerName.empty()){
                            playerName = "player";
                        }
                        scoreLoader.saveScore(playerName, score);
                        return 0;
                    }
                }
                else mainMenuButton->setTexture(mainMenuTexture);
                
                if (event.type == sf::Event::TextEntered)
                {
                    if(event.text.unicode < 128 && event.text.unicode != 32 && playerName.size() < 16)
                    {
                        playerName += static_cast<char>(event.text.unicode);
                        playerNameText->setString(playerName);
                    }
                    if(event.text.unicode == 8 && playerName.size() > 1)
                    {
                        playerName.resize(playerName.size()-2);
                        playerNameText->setString(playerName);
                    }
                }
            }
            
            window.clear();
            window.draw(*background, &backgroundShader);
            window.draw(*logo);
            window.draw(menuBackground);
            window.draw(*mainMenuButton);
            window.draw(*scoreText);
            window.draw(*playerNameText);
            window.display();
            
        }
        
        return -1;
    }
    
};
#endif