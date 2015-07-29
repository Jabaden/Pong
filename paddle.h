#include <SFML/Graphics.hpp>

using namespace std;

class paddle{
private:
	using sVector = vector<sf::Sprite>; //vector of sprites
	int count;
	double pSpeed = .01;
	sVector pdl;
public:
	paddle(sf::Texture* txt, int size, int player); // 1 = player...1, 2 = player 2
	void drawPaddle(sf::RenderWindow* wnd);
	void movePaddle(sf::Clock* clk, bool direction);//true is up , false is down
};