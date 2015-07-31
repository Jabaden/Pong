//header file for the ball class
#ifndef BALL_H
#define BALL_H
#include <SFML/Graphics.hpp>
#include "paddle.h"
using namespace std;

class ball{
	private: 
		int direction;
		float speed;
		sf::Sprite* sprite;
		float xVelocity;
		float yVelocity;
		sf::FloatRect bBox;
	public:
		ball(sf::Sprite* spright);

		sf::Sprite* getSprite();
		sf::FloatRect getBB();

		void changeTexture(sf::Texture* Txt);
		void moveBall(sf::Clock* clk);
		void reverseX();

		bool checkLeft();
		bool checkRight();
		bool checkTop();
		bool checkBot();
		bool checkCollision(paddle pdl);
};
#endif