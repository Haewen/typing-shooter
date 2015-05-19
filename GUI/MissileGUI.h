#ifndef MISSILEGUI_H
#define MISSILEGUI_H

#include <SFML/Graphics.hpp>
#include "../Logic/Missile.h"

/**
@brief Body of a missile
@author Benjamin Ferenc Hajas, Daniel Eke
*/

class MissileGUI : public sf::Drawable
{
public:
	/**
		@brief Creates a body for a missile.
		@param missile	Reference to a missile in logic.
	*/
	MissileGUI(Missile &missile);
	/**
		@brief Draws the missile.
	*/
	void draw(sf::RenderTarget& target, sf::RenderStates states) const;
	/**
	@brief Changes the position of the missile.
	@param position	The new position of the missile. 
	*/
	void setPosition(sf::Vector2f position);
protected:
	/**
	@brief The body of the missile.
	*/
	sf::RectangleShape body;
	/**
	@brief The missile's representation in logic.
	*/
	Missile* missile;
};

#endif //MISSILEGUI_H