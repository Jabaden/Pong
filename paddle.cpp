#include "paddle.h"
#include <stdio.h>
#include <iostream>

paddle::paddle(sf::Texture* txt, int size, int player){
	for (int i = 0; i < size; i++){
		sf::Sprite temp;
		temp.setTexture(*txt, true);
		int tempHeight;
		tempHeight = temp.getGlobalBounds().height;
		//temp.setScale()
		if (player != 1){
			temp.setPosition(1180, (0 + (tempHeight * i)));
		}
		else{
			temp.setPosition(0, (0 + (tempHeight * i)));
		}
		
		pdl.push_back(temp);
	}
}
void paddle::drawPaddle(sf::RenderWindow* wnd){
	for (auto itor = pdl.begin(); itor != pdl.end(); itor++){
		wnd->draw(*itor);
	}
}
//TODO REMOVE CLOCK STUFF
void paddle::movePaddle(sf::Clock* clk, bool direction){
	float delta = clk->restart().asSeconds();
	if (direction){
		for (auto itor = pdl.begin(); itor != pdl.end(); itor++){
			itor->move(0, -pSpeed);
		}
	}
	else{
		for (auto itor = pdl.begin(); itor != pdl.end(); itor++){
			itor->move(0, pSpeed);
		}
	}
	

}