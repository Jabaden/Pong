#include <stdio.h>
#include <iostream>
#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>
#include "ball.h"
#include "paddle.h"


//THIS IS A BIG OL TEST

using namespace std;
int main()
{
	const int gameWidth = 1200;
	const int gameHeight = 600;
	sf::Clock clock;
	sf::Clock leftClock;
	sf::Clock rightCLock;
	string testString = "omgwtfbbq";
	sf::RenderWindow window(sf::VideoMode(gameWidth, gameHeight), "SFML IS WORKING");
	sf::Texture ballTexture;
	if (!ballTexture.loadFromFile("ball.png")){
		return EXIT_FAILURE;
	}
	sf::Texture faceTexture;
	if (!faceTexture.loadFromFile("face.png")){
		return EXIT_FAILURE;
	}

	sf::Texture* paddleTexture = new sf::Texture();
	if (!paddleTexture->loadFromFile("paddle.png")){
		return EXIT_FAILURE;
	}

	sf::Sprite* ballPtr;
	ballPtr = new sf::Sprite();
	ballPtr->setScale(0.25f, 0.25f);

	ballPtr->setTexture(ballTexture);
	window.setPosition(sf::Vector2i(10, 50));
	ball testBall(ballPtr);
	paddle testPaddle(paddleTexture, 3, 1); //left
	paddle testPaddle2(paddleTexture, 5, 2); 
	while (window.isOpen())
	{
		sf::Event event;
		
		while (window.pollEvent(event))
		{
			if (event.type == sf::Event::Closed)
				window.close();
			//if (event.text.unicode < 128){
				//window.setTitle(testString);
				//gameBall.setTexture(ballTexture, true);
			//}
			
		}
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::W)){
			testPaddle.movePaddle(&leftClock, true);
		}
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::S)){
			testPaddle.movePaddle(&leftClock, false);
		}

		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up)){
			testPaddle2.movePaddle(&leftClock, true);
		}
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down)){
			testPaddle2.movePaddle(&leftClock, false);
		}
		testBall.moveBall(&clock);
		
		if (testBall.checkLeft() == true){
			window.close();
		}
		if (testBall.checkRight() == true){
			window.close();
		}

		if ((testBall.getSprite()->getPosition().x > gameWidth * .90)){
			if (testBall.checkCollision(testPaddle2) == true){
				window.setTitle("collided with right");
				testBall.reverseX();
			}
		}
		if (testBall.getSprite()->getPosition().x < gameWidth * .2){
			if (testBall.checkCollision(testPaddle) == true){
				window.setTitle("collided with left");
				testBall.reverseX();
			}
		}
		window.clear(sf::Color::White);
		window.draw(*(testBall.getSprite()));
		testPaddle.drawPaddle(&window);
		testPaddle2.drawPaddle(&window);
		window.display();
	}

	return 0;
}