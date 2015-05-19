/**
Score Scene
@author Dániel Eke
*/

#include "Scene.cpp"
#include "../../Logic/Position.h"
#include "../../Logic/ScoreLoader.h"
#include <vector>
#include <iostream>
#include <sstream>
#include <iomanip>
#include <SFML/Audio.hpp>

#ifndef SCORE_SCENE
#define SCORE_SCENE
class ScoreScene : public Scene
{
    int run(sf::RenderWindow &window)
    {
        Position resolution(window.getSize().x, window.getSize().y);
        ScoreLoader scoreLoader;
        
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
        sf::Vector2f backgroundSize = sf::Vector2f(400, 300);
        sf::Texture *menuTexture = new sf::Texture;
        menuTexture->loadFromFile("Resources/Backgrounds/menu_background.png");
        menuBackground.setTexture(menuTexture);
        menuBackground.setSize(backgroundSize);
        menuBackground.setOrigin(sf::Vector2f(menuBackground.getSize().x / 2, menuBackground.getSize().y / 2));
        menuBackground.setPosition(sf::Vector2f(resolution.getX() / 2, resolution.getY() / 7*4.5));
        
        // Loading Scores
        std::vector<sf::Text*>scores;
        sf::Font* f = new sf::Font();
        f->loadFromFile("Resources/Fonts/Ubuntu-Regular.ttf");
        
        std::vector<Score> scoreData = scoreLoader.getTopScore();
        for(int i = 0; i < scoreData.size(); i++){
            std::stringstream indStream;
            std::stringstream valStream;
            std::stringstream nameStream;
            indStream << std::setfill('0') << std::setw(2) << i+1;
            valStream << std::setfill('0') << std::setw(6) << scoreData[i].value;
            // TODO: lehetne szebben is
            if(scoreData[i].name.size() > 10){
                scoreData[i].name.resize(13);
                scoreData[i].name[10] = '.';
                scoreData[i].name[11] = '.';
                scoreData[i].name[12] = '.';
            }
            
            std::string scoreRow = "" + indStream.str() + ".\t\t" + valStream.str() + "\t\t " + scoreData[i].name;
            sf::Text* text = new sf::Text(scoreRow,*f);
            text->setCharacterSize(23);
            text->setStyle(sf::Text::Style::Bold);
            text->setColor(sf::Color::White);
            text->setPosition(sf::Vector2f((resolution.getX() / 2 - backgroundSize.x / 2) + 10, (resolution.getY() / 7*4.5 - backgroundSize.y / 2) + 10 + i * 20));
            
            scores.push_back(text);
        }
        
        if(scores.size() == 0){
            sf::Text* text = new sf::Text("No scores yet",*f);
            text->setCharacterSize(23);
            text->setStyle(sf::Text::Style::Bold);
            sf::FloatRect textRect = text->getLocalBounds();
            text->setOrigin(textRect.left + textRect.width/2.0f, textRect.top  + textRect.height/2.0f);
            text->setColor(sf::Color::White);
            text->setPosition(sf::Vector2f(resolution.getX() / 2, resolution.getY() / 2 - 20));
            scores.push_back(text);
        }
        
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
        backButton->setPosition(sf::Vector2f(resolution.getX() / 2, scores.back()->getPosition().y + 50));

		//button sound
		bool backButtonS = true;

		
        
        
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
					hoverSound(backButtonS);
					backButtonS = false;
                    backButton->setTexture(backTextureS);
                    if(event.type == sf::Event::MouseButtonReleased)
                    {
						backButtonS = true;
                        return 0;
                    }
                }
				else {
					backButton->setTexture(backTexture); backButtonS = true;
				}
            }
            
            window.clear();
            window.draw(*background);
            window.draw(*logo);
            window.draw(menuBackground);
            window.draw(*backButton);
            for (auto &text : scores)
            {
                window.draw(*text);
            }
            window.display();
            
        }
        
        return -1;
    }
    
};
#endif