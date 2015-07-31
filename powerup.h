#ifndef POWERUP_H
#define POWERUP_H
#include <SFML/Graphics.hpp>

class powerup{
private:
	sf::Sprite* sprite;
	sf::FloatRect bBox;
public:
	powerup(sf::Sprite* spr);
	sf::Sprite* getSprite();
};
#endif