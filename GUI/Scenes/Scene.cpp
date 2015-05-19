#ifndef SCENE
#define SCENE

#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>

/**
@brief Scene Skeleton
@author Benjamin Ferenc Hajas, Balazs Katona, Daniel Eke
*/

class Scene
{
public:
	/**
	@brief Runs the scene.
	@param window	The window to run the scene in.
	*/
	virtual int run(sf::RenderWindow &window) = 0;
	/**
		@brief Button spacing.
	*/
    int buttonSpacing = 70;
	/**
	@brief Plays a sound on a button hover.
	@param f	A bool to tell if the sound is already playing or not.
	*/
	void hoverSound(bool f)
	{
		if (f)
		{
			hbuffer.loadFromFile("Resources/Sounds/ooa.wav");
			hsound.setBuffer(hbuffer);
			hsound.setVolume(50);
			hsound.play();
		}	
	}

	//Hover sound
	/**
		@brief Sound buffer.
	*/
	sf::SoundBuffer hbuffer;
	/**
		@brief Sound.
	*/
	sf::Sound hsound;

	
};
#endif