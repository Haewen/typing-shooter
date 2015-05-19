#include <SFML/Graphics.hpp>
#include "Logic/GameLogic.h"
#include "GUI/EnemyGUI.h"
#include "GUI/MissileGUI.h"
#include "GUI/Scenes/Scene.cpp"
#include "GUI/Scenes/MainMenu.cpp"
#include "GUI/Scenes/ScoreScene.cpp"
#include "GUI/Scenes/GameScene.cpp"

#include <iostream>


/** @mainpage Typing Shooter

@section intro_sec Introduction
@subsection  intro_team Our Team
This project was created for the university course Tools of Software Projects. \n
Our team consisted of 3 people:
\li Balazs Katona - <b> Makefile, Sounds and Music </b>
\li Daniel Eke - <b> Testing, Menus, helped with %GameLogic</b>
\li Benjamin Ferenc Hajas - <b> %GameLogic, %GameScene, Documentation, helped with Menus </b>
@subsection  intro_idea The Idea
Our goal was to create a two-dimensional game very similar to an existing one.
@image html img/original_game.png "The original game"
The game can be found at http://phoboslab.org/ztype/ . \n

@subsection  intro_game The game
The game itself is an infinite shooter. \n
Each wave of enemies is stronger than the previous one. \n
After a while the player is not able to kill every enemy on screen so they lose.
\n \n
On every enemy there is a random English word from the official Scrabbler dictionary.
If the player can type in the word before an enemy gets to them, the enemy dies and the player gets points.
@subsection  intro_game Realization

We decided to make this game in C++.\n
Since Daniel worked on Macintosh and Me and Balazs both worked on Windows, we needed a cross platform library. \n
We decided we would use <a href="http://www.sfml-dev.org">SFML</a> because it is very well documented and simple to use.

\n We used GTest for the tests, we use a makefile to build and Doxygen for the documentation.

@subsection intro_screenshots Screenshots
@image html img/main_menu.png "Main Menu"
@image html img/high_score.png "High scores"
@image html img/game_scene.png "Game Scene"

@subsection intro_future Future improvements
@li Game %scene change could wait for enemies to explode.
@li Support for more resolutions.
@li Options menu
@li Explosion effects
@li More enemy types
@li Animations
@li Combo system
@li Gamemodes

@author Benjamin Ferenc Hajas
*/

/**
Basic display with event loop.
Opens and manages a window and its contents.
@author Benjamin Ferenc Hajas
*/
int main()
{	
	//Application variables
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

