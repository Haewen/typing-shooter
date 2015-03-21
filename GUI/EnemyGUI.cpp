/**
	Creates a body for an enemy
	@author Benjamin Ferenc Hajas
*/

#include "EnemyGUI.h"

EnemyGUI::EnemyGUI(Enemy &enemy)
{
	body.setFillColor(sf::Color::Red);
	body.setSize(sf::Vector2f(10, 10));
	body.setOrigin(5, 5);
	body.setPosition(sf::Vector2f(enemy.getPosition().getX(), enemy.getPosition().getY()));
	
	sf::Font* f = new sf::Font();
	f->loadFromFile("arial.ttf");
	text = new sf::Text(enemy.getText(),*f);
	text->setColor(sf::Color::White);
	text->setPosition(sf::Vector2f(body.getPosition().x + body.getSize().x, body.getPosition().y));
	text->setCharacterSize(13);
	text->setStyle(sf::Text::Style::Bold);
}

void EnemyGUI::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
	target.draw(body,states);
	target.draw(*text,states);
}

void EnemyGUI::setPosition(sf::Vector2f position)
{
	body.setPosition(position);
	text->setPosition(sf::Vector2f(body.getPosition().x + body.getSize().x + 1, body.getPosition().y - body.getSize().y/2- text->getLocalBounds().top));
}