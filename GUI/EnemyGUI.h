/**
	Creates a body for an enemy
	@author Benjamin Ferenc Hajas
*/

#ifndef ENEMYGUI_H
#define ENEMYGUI_H

#include <SFML/Graphics.hpp>
#include "../Logic/Enemy.h"

class EnemyGUI : public sf::Drawable
{
public:
	EnemyGUI(Enemy &enemy);
	void draw(sf::RenderTarget& target, sf::RenderStates states) const;
	void setPosition(sf::Vector2f position);
	void setAsTarget();
	void updateText();
protected:
	sf::RectangleShape body;
	sf::Text* text;
	Enemy* enemy;
    float rotateSpeed;
};

#endif //ENEMYGUI_H