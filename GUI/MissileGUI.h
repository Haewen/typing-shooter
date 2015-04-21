/**
Creates a body for a missile
@author Benjamin Ferenc Hajas, Dániel Eke
*/

#ifndef MISSILEGUI_H
#define MISSILEGUI_H

#include <SFML/Graphics.hpp>
#include "../Logic/Missile.h"

class MissileGUI : public sf::Drawable
{
public:
	MissileGUI(Missile &missile);
	void draw(sf::RenderTarget& target, sf::RenderStates states) const;
	void setPosition(sf::Vector2f position);
protected:
	sf::RectangleShape body;
	Missile* missile;
};

#endif //MISSILEGUI_H