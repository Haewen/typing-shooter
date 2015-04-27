#include "Scene.cpp"
#include "../../Logic/Position.h"
#include <vector>
#include <iostream>

#ifndef OPTIONS_SCENE
#define OPTIONS_SCENE
class OptionsScene : public Scene
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
        
        
        //Loading backButton
        sf::RectangleShape *backButton = new sf::RectangleShape();
        sf::Texture *backTexture = new sf::Texture;
        backTexture->loadFromFile("Resources/Menu/back_button.png");
        backTexture->setSmooth(true);
        
        sf::Texture *backTextureS = new sf::Texture;
        backTextureS->loadFromFile("Resources/Menu/back_button_selected.png");
        backTextureS->setSmooth(true);
        
        backButton->setTexture(backTexture);
        backButton->setSize(sf::Vector2f(500 / 2, 100 / 2));
        backButton->setOrigin(sf::Vector2f(backButton->getSize().x / 2, backButton->getSize().y / 2));
        backButton->setPosition(sf::Vector2f(resolution.getX() / 2, resolution.getY() / 2));
        
        
        while (window.isOpen())
        {
            sf::Event event;
            while (window.pollEvent(event))
            {
                if (event.type == sf::Event::Closed)
                    window.close();
                
                sf::Vector2i mousePosition = sf::Mouse::getPosition(window);
                if (backButton->getGlobalBounds().contains(mousePosition.x, mousePosition.y))
                {
                    backButton->setTexture(backTextureS);
                    if (sf::Mouse::isButtonPressed(sf::Mouse::Left))
                    {
                        return 0;
                    }
                }
                else backButton->setTexture(backTexture);
            }
            
            window.clear();
            window.draw(*background);
            window.draw(*logo);
            window.draw(menuBackground);
            window.draw(*backButton);
            window.display();
            
        }
        return -1;
    }
    
};
#endif