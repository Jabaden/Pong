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

	sf::Texture paddleTexture;
	if (!paddleTexture.loadFromFile("paddle.png")){
		return EXIT_FAILURE;
	}
	sf::Texture* paddleTexturePtr = &paddleTexture;

	sf::Sprite* ballPtr;
	sf::Sprite gameBall;
	gameBall.setScale(0.25f, 0.25f);
	ballPtr = &gameBall;
	gameBall.setTexture(ballTexture);
	window.setPosition(sf::Vector2i(10, 50));
	ball testBall(ballPtr);
	paddle testPaddle(paddleTexturePtr, 3, 1);
	paddle testPaddle2(paddleTexturePtr, 3, 2);
	//testBall.changeTexture(&faceTexture);
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
		//float delta = clock.restart().asSeconds();
		//testBall.getSprite()->move(speed * delta, 0.f);
		testBall.moveBall(&clock);
		
		if (testBall.checkLeft() == true){
			window.close();
		}
		if (testBall.checkRight() == true){
			window.close();
		}

		window.clear(sf::Color::White);
		window.draw(*(testBall.getSprite()));
		testPaddle.drawPaddle(&window);
		testPaddle2.drawPaddle(&window);
		window.display();
	}

	return 0;
}