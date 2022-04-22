#pragma once
#include <SFML/Graphics.hpp>

// This struct is doubly linked list and to achive high performace we make a tail to insert at lat o(1)
/* The paramters which effect the time analysis
- is the use of doubly linked list not singly linked list .
-the tail we store at the end of the train make inseting at the end o(1)
- the speed of the train means the speed of render maens more time to reach snoopy
- the storing the counts of nodes inside the game help us to know the length of linked list
-



*/

struct node
{
	int posx, posy;
	int direction;
	// just an entity inside it texture
	sf::Sprite* s;
	// left and right link for doubly linked list

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
	NODE head, tail, cur;
	// for the game we store 3 pointers to first and last and another named it current
	int speed = 200;
	// count is the count of nodes inside the linked list
	int count = 0;
	int score = -1;
	sf::Vector2f snoopyPos;

private:
	// these cariballes is related to sfml tool

	sf::RenderWindow window;
	sf::Sprite TrainSprite;
	sf::Texture spriteSheet;
	sf::Sprite snoopy;
	sf::Event event;
	sf::Text Score;
	sf::Font font;
	sf::Texture Background;
	sf::Sprite bg;

private:
	// the description for all functions inside the souece file
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
