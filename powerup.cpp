#include <stdio.h>
#include <iostream>
#include "powerup.h"

powerup::powerup(sf::Sprite* spr){
	sprite = spr;
	sprite->setPosition(1200.f / 3.f, 600.f / 3.f);
	bBox = sprite->getGlobalBounds();
}
sf::Sprite* powerup::getSprite(){
	return this->sprite;
}