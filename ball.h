//header file for the ball class
#include <SFML/Graphics.hpp>
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

		bool checkLeft();
		bool checkRight();
		bool checkTop();
		bool checkBot();


};