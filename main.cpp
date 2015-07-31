#include <stdio.h>
#include <iostream>
#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include "ball.h"
#include "paddle.h"
#include "powerup.h"


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
	sf::RenderWindow window(sf::VideoMode(gameWidth, gameHeight), "Pong_John_Baden");
	//------------------------------------------Sounds--------------------------------------------
	sf::SoundBuffer buffer;
	if (!buffer.loadFromFile("applause2_x.wav"))
		return -1;
	sf::Sound applause;
	applause.setBuffer(buffer);

	
	//------------------------------------------TEXTURES-------------------------------------------
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

	sf::Texture powerupTexture;
	if (!powerupTexture.loadFromFile("heart.png")){
		return EXIT_FAILURE;
	}
	//---------------------------------------TEXTURES END------------------------------------------
	sf::Sprite* ballPtr;
	sf::Sprite* puPtr;
	puPtr = new sf::Sprite();
	puPtr->setScale(0.25f, 0.25f);
	puPtr->setTexture(powerupTexture);

	ballPtr = new sf::Sprite();
	ballPtr->setScale(0.25f, 0.25f);
	ballPtr->setTexture(ballTexture);

	window.setPosition(sf::Vector2i(10, 50));
	ball testBall(ballPtr);
	paddle testPaddle(paddleTexture, 3, 1); //left
	paddle testPaddle2(paddleTexture, 5, 2); 

	sf::Sprite segment;
	segment.setTexture(*paddleTexture, true);
	//------------------------------------------------TESTING---------------------------
	int lastHeight;
	lastHeight = segment.getGlobalBounds().height;
	
	//-----------------------------------------------------------------------------------

	powerup powerUp(puPtr);


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
		//----------------------------------KeyBoard Mapping--------------------------------
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
		//-----------------------------------KeyBoard Mapping End---------------------------

		testBall.moveBall(&clock);//moving the ball around 

		//---------------------------------Collision Testing---------------------------------
		if (testBall.checkLeft() == true){
			window.close();
		}
		if (testBall.checkRight() == true){
			window.close();
		}
		//--------BALL AND POWERUP
		if (testBall.checkPowerupCollision(puPtr) == true){
			
			//finding the last element in the vector and getting its position to insert the segement in the correct place
			if (testBall.getHitBy() == false){ //came from the right
				segment.setPosition(1180, (testPaddle2.getPVector()->back().getPosition().y) + lastHeight);
				testPaddle2.getPVector()->push_back(segment);
			} 
			else{
				segment.setPosition(0, (testPaddle.getPVector()->back().getPosition().y) + lastHeight);
				testPaddle.getPVector()->push_back(segment);
			}
			powerUp.getSprite()->setPosition(200, 200);
			
		}

		if ((testBall.getSprite()->getPosition().x > gameWidth * .90)){
			if (testBall.checkCollision(testPaddle2) == true){
				window.setTitle("collided with right");
				testBall.swapHitBy();
				applause.play();
				testBall.reverseX();
			}
		}
		if (testBall.getSprite()->getPosition().x < gameWidth * .2){
			if (testBall.checkCollision(testPaddle) == true){
				window.setTitle("collided with left");
				
				testBall.reverseX();
			}
		}
		//------------------------------Collision Testing End------------------------------

		//------------------------------Rendering------------------------------------------
		window.clear(sf::Color::White);

		window.draw(*(testBall.getSprite()));
		testPaddle.drawPaddle(&window);
		testPaddle2.drawPaddle(&window);
		window.draw(*(powerUp.getSprite()));
		window.display();
		//------------------------------Rendering End--------------------------------------
	}

	return 0;
}