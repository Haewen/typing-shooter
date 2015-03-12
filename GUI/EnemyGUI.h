#pragma once
#include <SFML/Graphics.hpp>
#include "../Logic/Enemy.h"

class EnemyGUI : public sf::Drawable
{
public:
	EnemyGUI(Enemy &enemy);
	void draw(sf::RenderTarget& target, sf::RenderStates states) const;
	void setPosition(sf::Vector2f position);
protected:
	sf::RectangleShape body;
	sf::Text* text;
};

