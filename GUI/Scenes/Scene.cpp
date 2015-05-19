/**
Scene Skeleton
@author Benjamin Ferenc Hajas, Balázs Katona
*/

#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>

#ifndef SCENE
#define SCENE
class Scene
{
public:
	virtual int run(sf::RenderWindow &window) = 0;
    int buttonSpacing = 70;
	void hoverSound()
	{
			hbuffer.loadFromFile("Resources/Sounds/ooa.wav");
			hsound.setBuffer(hbuffer);
			hsound.setVolume(50);
			hsound.play();
		
	}
	//Hover sound
	sf::SoundBuffer hbuffer;
	sf::Sound hsound;
};
#endif