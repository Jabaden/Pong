#include "ball.h"
#include "paddle.h"
#include <stdio.h>
#include <iostream>
#include <cmath>

ball::ball(sf::Sprite* spright){
	sprite = spright;
	speed = 100.f;
	sprite->setPosition(1200.f / 2.f, 600.f / 2.f);
	xVelocity = 300.f;
	yVelocity = -300.f;
	bBox = sprite->getGlobalBounds();
}

sf::Sprite* ball::getSprite(){
	return sprite;
}

sf::FloatRect ball::getBB(){
	return bBox;
}

void ball::changeTexture(sf::Texture* txt){
	this->sprite->setTexture(*txt, true);
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
		yVelocity = abs(yVelocity);
	}
	if (this->checkBot() == true){
		yVelocity = -(abs(yVelocity));
	}
	this->sprite->move(xVelocity * delta, yVelocity * delta);
	//this->sprite->move(.02, 0.f);
}
bool ball::checkCollision(paddle Paddle){
	auto tempItor = Paddle.getPVector()->begin();
	for (auto itor = Paddle.getPVector()->begin(); itor != Paddle.getPVector()->end(); itor++){
		if (this->getSprite()->getGlobalBounds().intersects(itor->getGlobalBounds())){
			//if (itor == Paddle.getPVector()->begin() && next(itor) == Paddle.getPVector()->end()){
			//Paddle.getPVector()->clear();
			//}
			if (itor == Paddle.getPVector()->begin()){
				itor = Paddle.getPVector()->erase(itor);
				if (this->yVelocity > 0){
					this->yVelocity = fmin(-550.f, -(yVelocity * 2.0f));
					this->xVelocity /= 1.1f;
					//this->xVelocity *= (2.0f);
					//this->xVelocity = fmax(550.f, (xVelocity * 2.0f));
					
				}
				return true;
			}
			if (itor != Paddle.getPVector()->end() && next(itor) == Paddle.getPVector()->end()){
				itor = Paddle.getPVector()->erase(itor);
				if (this->yVelocity < 0){
					this->yVelocity *= (-1.f);
					//this->xVelocity *= (2.0f);
					this->xVelocity = fmax(550.f, (xVelocity * 2.0f));
				}
				return true;
			}
			this->yVelocity = 300.f;
			//this->yVelocity = fmin(550.f, (yVelocity * 2.0f));
			this->xVelocity = 300.f;
			itor = Paddle.getPVector()->erase(itor);
			return true;
		}
	}
	return false;
}
void ball::reverseX(){
	this->xVelocity *= (-1.f);
}

bool ball::getHitBy(){
	return hitByLeft;
}

bool ball::checkPowerupCollision(sf::Sprite* pUp){
	if (this->getSprite()->getGlobalBounds().intersects(pUp->getGlobalBounds())){
		return true;
	}
	return false;
}

void ball::swapHitBy(){
	if (this->hitByLeft == true){
		this->hitByLeft = false;
	}
	else{
		this->hitByLeft = true;
	}
}

void ball::resetBall(){
	this->sprite->setPosition(1200.f / 2.f, 600.f / 2.f);
	this->xVelocity = 300.f;
	this->yVelocity = -300.f;
}