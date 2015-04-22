#include <SFML/Graphics.hpp>

#ifndef SCENE
#define SCENE
class Scene
{
public:
	virtual int run(sf::RenderWindow &window) = 0;
};
#endif