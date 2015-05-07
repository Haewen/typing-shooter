/**
	Basic display with event loop.
	Opens and manages a window and its contents.
	@author Benjamin Ferenc Hajas
*/

#include <SFML/Graphics.hpp>
#include "Logic/GameLogic.h"
#include "GUI/EnemyGUI.h"
#include "GUI/MissileGUI.h"
#include "GUI/Scenes/Scene.cpp"
#include "GUI/Scenes/MainMenu.cpp"
#include "GUI/Scenes/ScoreScene.cpp"
#include "GUI/Scenes/GameScene.cpp"

#include <iostream>

int main()
{	
	//Applications variables
	std::vector<Scene*> scenes;
	int currentScene = 0;
	MainMenu mainMenu;
	scenes.push_back(&mainMenu);
    GameScene gameScene;
    scenes.push_back(&gameScene);
    ScoreScene scoreScene;
    scenes.push_back(&scoreScene);

	//Creating window
	sf::RenderWindow window(sf::VideoMode(800, 600), "Typing Shooter", sf::Style::Close);
	window.setVerticalSyncEnabled(true);
	Position resolution(window.getSize().x, window.getSize().y);

	while (currentScene >= 0)
	{
		currentScene = scenes[currentScene]->run(window);
	}
	return 0;

}

