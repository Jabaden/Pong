#include <stdio.h>
#include <iostream>
#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include "ball.h"
#include "paddle.h"
#include "powerup.h"
#include "time.h"

using namespace std;
void resetAllTheThings(sf::RenderWindow* window, paddle pdl1, paddle pdl2, sf::Sprite seg, ball bll, sf::Text l, sf::Text r); //forward identifier
//I know globals arent the greatest, but a few shouldnt hurt for something simple like this.
int lScore = 0;
int rScore = 0;
bool gameOver = false;

int main()
{
	const int gameWidth = 1200;
	const int gameHeight = 600;
	srand(time(NULL));
	int rHeight = 0;
	int rWidth = 0;
	rHeight = rand() % 580 + 20;
	rWidth = rand() % 1000 + 200;
	//------------------------------------------Clocks--------------------------------------------
	sf::Clock clock;
	sf::Clock leftClock;
	sf::Clock rightCLock;
	//------------------------------------------Window--------------------------------------------

	sf::RenderWindow window(sf::VideoMode(gameWidth, gameHeight), "Pong_John_Baden");

	//------------------------------------------Sounds--------------------------------------------

	sf::SoundBuffer buffer;
	if (!buffer.loadFromFile("applause2_x.wav"))
		return -1;
	sf::Sound applause;
	applause.setBuffer(buffer);
	applause.setVolume(40);

	if (!buffer.loadFromFile("boing_x.wav"))
		return -1;
	sf::Sound boing;
	boing.setBuffer(buffer);
	//------------------------------------------FONT AND TEXT--------------------------------------
	sf::Font font;
	if (!font.loadFromFile("pingpong.ttf")){
		return -1;
	}
	sf::Text leftScore;
	leftScore.setFont(font);
	leftScore.setColor(sf::Color::Red);
	leftScore.setString("0");
	leftScore.setPosition((gameWidth / 2) - 200, gameHeight - 550);

	sf::Text rightScore;
	rightScore.setFont(font);
	rightScore.setColor(sf::Color::Red);
	rightScore.setString("0");
	rightScore.setPosition((gameWidth / 2) + 200, gameHeight - 550);

	sf::Text over;
	over.setFont(font);
	over.setColor(sf::Color::Red);
	over.setString("Game Over! Press R to reset!");
	over.setPosition((gameWidth / 2) - 100, gameHeight - 200);

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

	//---------------------------------------SPRITES-----------------------------------------------
	sf::Sprite* ballPtr;
	sf::Sprite* puPtr;
	puPtr = new sf::Sprite();
	puPtr->setScale(0.25f, 0.25f);
	puPtr->setTexture(powerupTexture);

	ballPtr = new sf::Sprite();
	ballPtr->setScale(0.15f, 0.15f);
	ballPtr->setTexture(ballTexture, true);

	window.setPosition(sf::Vector2i(10, 50));
	ball testBall(ballPtr);
	paddle testPaddle(paddleTexture, 5, 1); //left
	paddle testPaddle2(paddleTexture, 5, 2); 

	sf::Sprite segment;
	segment.setTexture(*paddleTexture, true);
	//--------------------------------------SPRITES END------------------------------------------

	//------------------------------------------------TESTING------------------------------------
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
			if (gameOver == true){
				if (event.text.unicode == 17){ //17 is 'R' on a keyboard
					resetAllTheThings(&window, testPaddle, testPaddle2, segment, testBall, leftScore, rightScore);
					//window.setTitle(testString);
					//gameBall.setTexture(ballTexture, true);
				}
			}
			
		}
		leftScore.setString(to_string(lScore));
		rightScore.setString(to_string(rScore));
		if (lScore == 2 || rScore == 2){ gameOver = true; }
		if (gameOver == false){
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
				if (!buffer.loadFromFile("applause2_x.wav"))
					return -1;
				applause.play();
				testBall.resetBall();
				testPaddle.resetPaddle(segment, 0);
				testPaddle2.resetPaddle(segment, 1);
				rScore++;
				rightScore.setString(to_string(rScore));
			}
			if (testBall.checkRight() == true){
				if (!buffer.loadFromFile("applause2_x.wav"))
					return -1;
				testBall.resetBall();
				applause.play();
				testPaddle.resetPaddle(segment, 0);
				testPaddle2.resetPaddle(segment, 1);
				lScore++;
				leftScore.setString(to_string(lScore));

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
				rHeight = rand() % 580 + 20;
				rWidth = rand() % 1000 + 200;
				powerUp.getSprite()->setPosition(rWidth, rHeight);

			}

			if ((testBall.getSprite()->getPosition().x > gameWidth * .90)){
				if (testBall.checkCollision(testPaddle2) == true){
					window.setTitle("collided with right");
					if (!buffer.loadFromFile("boing_x.wav"))
						return -1;
					testBall.swapHitBy();
					boing.play();
					testBall.reverseX();
				}
			}
			if (testBall.getSprite()->getPosition().x < gameWidth * .2){
				if (testBall.checkCollision(testPaddle) == true){
					window.setTitle("collided with left");
					if (!buffer.loadFromFile("boing_x.wav"))
						return -1;
					testBall.swapHitBy();
					boing.play();
					testBall.reverseX();
				}
			}
			//------------------------------Collision Testing End------------------------------
		}
		//------------------------------Rendering------------------------------------------
		window.clear(sf::Color::White);
		if (gameOver == false){
			window.draw(leftScore);
			window.draw(rightScore);
			window.draw(*(testBall.getSprite()));
			testPaddle.drawPaddle(&window);
			testPaddle2.drawPaddle(&window);
			window.draw(*(powerUp.getSprite()));
		}
		if (gameOver == true){
			window.draw(over);
		}

		window.display();
		//------------------------------Rendering End--------------------------------------
	}

	return 0;
}
//hiding the reset function down here, I couldnt decide what object this kind of thing belonged to, so I just put it in main.cpp
void resetAllTheThings(sf::RenderWindow* window, paddle pdl1, paddle pdl2, sf::Sprite seg, ball bll, sf::Text l, sf::Text r){
	l.setString("test");
	r.setString("test");
	lScore = 0;
	rScore = 0;
	gameOver = false;
	pdl1.resetPaddle(seg, 0);
	pdl2.resetPaddle(seg, 1);
	bll.resetBall();
	
}