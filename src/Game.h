#pragma once
#include <SFML/Graphics.hpp>

struct node
{
	int posx, posy;
	int direction;
	sf::Sprite* s;
	struct node* llink;
	struct node* rlink;
};
typedef struct node* NODE;
enum direction
{
	up,
	down,
	left,
	right
};
class Game
{
private:
	NODE head1, tail1, cur1;
	NODE head2, tail2, cur2;
	//////////
	int speed1 = 200;
	int count1 = 0;
	int score1 = -1;
	///////////////
	int speed2 = 200;
	int count2 = 0;
	int score2 = -1;
	////////
	sf::Vector2f snoopyPos;

private:
	sf::RenderWindow window;
	sf::Sprite TrainSprite1;
	sf::Texture spriteSheet1;
	/////////////
	sf::Sprite TrainSprite2;
	sf::Texture spriteSheet2;
	//////////
	sf::Sprite snoopy;
	sf::Event event;
	// sf::Event event2;
	///must be Event 2
	////////
	sf::Text Score1;
	sf::Font font1;
	////
	sf::Text Score2;
	sf::Font font2;
	//////
	sf::Texture Background;
	sf::Sprite bg;

private:
	void Update();
	void Render();
	void Start();
	void LoadSprites();

	NODE insertHead(NODE head, sf::Sprite* sprite);
	NODE deleteTail(NODE tail);

	void processEvents();

private:
	void setTrailingSprite(NODE node, sf::Sprite* sp);
	void setHeadSprite(NODE head, sf::Sprite* sp);
	sf::Vector2f getSnoopyCoords();
	void HandleSnoopyTouched();
	bool isSnoopyTouched(NODE head, sf::Sprite* snoopy);
	void checkIntersection(NODE head, sf::RenderWindow* window);

public:
	void Run();
};
