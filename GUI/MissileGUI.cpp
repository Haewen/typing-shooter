/**
Creates a body for a missile
@author Benjamin Ferenc Hajas
*/

#include "MissileGUI.h"

MissileGUI::MissileGUI(Missile &missile)
{
	this->missile = &missile;
	//body.setFillColor(sf::Color::Red);
	body.setSize(sf::Vector2f(10, 10));
	body.setOrigin(5, 5);
	body.setPosition(sf::Vector2f(missile.getPosition().getX(), missile.getPosition().getY()));
	sf::Texture* texture = new sf::Texture;
	texture->loadFromFile("Resources/missile.png");
	body.setTexture(texture);

}

void MissileGUI::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
	target.draw(body, states);
}

void MissileGUI::setPosition(sf::Vector2f position)
{
	body.setPosition(position);
}