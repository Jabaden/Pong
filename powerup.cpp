#include <stdio.h>
#include <iostream>
#include "powerup.h"

powerup::powerup(sf::Sprite* spr){
	sprite = spr;
	sprite->setPosition(1200.f / 2.f, 600.f / 2.f);
	bBox = sprite->getGlobalBounds();
}
sf::Sprite* powerup::getSprite(){
	return this->sprite;
}