#include "ball.h"
#include "paddle.h"
#include <stdio.h>
#include <iostream>

ball::ball(sf::Sprite* spright){
	sprite = spright;
	speed = 100.f;
	sprite->setPosition(1200.f / 2.f, 600.f / 2.f);
	xVelocity = 50.f;
	yVelocity = -50.f;
	bBox = sprite->getGlobalBounds();
}

sf::Sprite* ball::getSprite(){
	return sprite;
}

sf::FloatRect ball::getBB(){
	return bBox;
}

void ball::changeTexture(sf::Texture* txt){
	this->sprite->setTexture(*txt,true);
}

bool ball::checkLeft(){
	if (this->sprite->getPosition().x < 0.0f){
		return true;
	}
	else{
		return false;
	}
}

bool ball::checkRight(){
	if (this->sprite->getPosition().x > 1200.0f){
		return true;
	}
	else{
		return false;
	}
}
bool ball::checkTop(){
	if (this->sprite->getPosition().y < 0.0f){
		return true;
	}
	else{
		return false;
	}
}
bool ball::checkBot(){
	if (this->sprite->getPosition().y > 600.0f){
		return true;
	}
	else{
		return false;
	}
}
void ball::moveBall(sf::Clock* clk){
	//positive is down, and right
	//negative is left and up
	float delta = clk->restart().asSeconds();
	if (this->checkTop() == true){
		yVelocity *= -1.f;
	}
	if (this->checkBot() == true){
		yVelocity *= -1.f;
	}
	this->sprite->move(xVelocity * delta, yVelocity * delta);
	//this->sprite->move(.02, 0.f);
}
bool ball::checkCollision(paddle Paddle){
	for (auto itor = Paddle.getPVector()->begin(); itor != Paddle.getPVector()->end(); itor++){
		if (this->getSprite()->getGlobalBounds().intersects(itor->getGlobalBounds())){
			itor = Paddle.getPVector()->erase(itor);
			return true;
		}
	}
	return false;
}

void ball::reverseX(){
	this->xVelocity *= (-1.f);
}