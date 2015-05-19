/**
Pause Scene
@author Dániel Eke
*/

#include "Scene.cpp"
#include "../../Logic/Position.h"
#include <vector>
#include <iostream>

#ifndef PAUSE_SCENE
#define PAUSE_SCENE
class PauseScene : public Scene
{
    int run(sf::RenderWindow &window)
    {
        Position resolution(window.getSize().x, window.getSize().y);
		bool isFullScreen = false;
        
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
        mainMenuButton->setPosition(sf::Vector2f(resolution.getX() / 2, resolution.getY() / 2));
        
        //Loading resumeButton
        sf::RectangleShape *resumeButton = new sf::RectangleShape();
        sf::Texture *resumeTexture = new sf::Texture;
        resumeTexture->loadFromFile("Resources/Menu/resume_button.png");
        resumeTexture->setSmooth(true);
        
        sf::Texture *resumeTextureS = new sf::Texture;
        resumeTextureS->loadFromFile("Resources/Menu/resume_button_selected.png");
        resumeTextureS->setSmooth(true);
        
        resumeButton->setTexture(resumeTexture);
        resumeButton->setSize(sf::Vector2f(500 / 2, 100 / 2));
        resumeButton->setOrigin(sf::Vector2f(resumeButton->getSize().x / 2, resumeButton->getSize().y / 2));
        resumeButton->setPosition(sf::Vector2f(resolution.getX() / 2, resolution.getY() / 2 + buttonSpacing));
        
        
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

					if (event.key.code == sf::Keyboard::F && !isFullScreen)
					{
						window.create(sf::VideoMode(800, 600), "Typing Shooter", sf::Style::Fullscreen);
						isFullScreen = true;
					}

					else if (event.key.code == sf::Keyboard::F && isFullScreen)
					{
						window.create(sf::VideoMode(800, 600), "Typing Shooter", sf::Style::Close);
						isFullScreen = false;
					}

                }

                
                sf::Vector2i mousePosition = sf::Mouse::getPosition(window);
                if (resumeButton->getGlobalBounds().contains(mousePosition.x, mousePosition.y))
                {
					hoverSound();
                    resumeButton->setTexture(resumeTextureS);
                    if(event.type == sf::Event::MouseButtonReleased)
                    {
                        return -1;
                    }
                }
                else resumeButton->setTexture(resumeTexture);
                
                if (mainMenuButton->getGlobalBounds().contains(mousePosition.x, mousePosition.y))
                {
					hoverSound();
                    mainMenuButton->setTexture(mainMenuTextureS);
                    if(event.type == sf::Event::MouseButtonReleased)
                    {
                        return 0;
                    }
                }
                else mainMenuButton->setTexture(mainMenuTexture);
            }
            
            window.clear();
            window.draw(*background, &backgroundShader);
            window.draw(*logo);
            window.draw(menuBackground);
            window.draw(*mainMenuButton);
            window.draw(*resumeButton);
            window.display();
            
        }
        
        return -1;
    }
    
};
#endif