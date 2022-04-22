#include "Game.h"
#include <SFML/Graphics.hpp>
#include <iostream>
#define side 15
#define size 208.5

/*
important notice on the concept of motion
the motion is to insert at the head and delete from the tail it give us motionn when we render the seen


*/

/*

Describtion : inseet at the head of the train and change the postion after deletetion
input : the head of the train
output : void

 */
NODE Game::insertHead(NODE head, sf::Sprite* sprite)
{
	NODE temp;
	temp = (NODE)malloc(sizeof(struct node));
	switch (head->direction)
	{
		case direction(up):
			temp->posy = head->posy - side * 2;
			temp->posx = head->posx;
			break;
		case direction(down):
			temp->posy = head->posy + side * 2;
			temp->posx = head->posx;
			break;
		case direction(left):
			temp->posx = head->posx - side * 2;
			temp->posy = head->posy;
			break;
		case direction(right):
			temp->posx = head->posx + side * 2;
			temp->posy = head->posy;
			break;
		default:
			break;
	}
	temp->direction = head->direction;
	temp->s = sprite;
	temp->llink = NULL;
	temp->rlink = head;
	head->llink = temp;
	return temp;
}
/*

Describtion : delte the tail of the train to give the concept of motion
input :the tail we store to acive high performance

output :

 */

NODE Game::deleteTail(NODE tail)
{
	NODE temp;
	temp = tail->llink;
	temp->rlink = NULL;
	free(tail);
	tail = NULL;
	return temp;
}

/*

Describtion :inside this function we update all game
1- if the train git out of the window return it back
2- hadle if the train touch the snoopy
3-handle the motion by is=nsert at head and delete at tail
4- check if the train intersect with it self to teminate the game
input : no
output : void

 */
void Game::Update()
{
	// return the train back to window
	if (head->posx > 810)
		head->posx = 0;
	if (head->posx < 0)
		head->posx = 810;
	if (head->posy > 600)
		head->posy = 0;
	if (head->posy < 0)
		head->posy = 600;
	HandleSnoopyTouched();
	// call this function every frame
	head = insertHead(head, &TrainSprite);
	tail = deleteTail(tail);
	checkIntersection(head, &window);
	count = 0;
}
/*

Describtion :the steps
1- is to use sfml tool to load the sprite entity
2- create head node
3- intilaze the postin 0,0 and the direction to right
4- and the tail is the head initially
5-set the snoopy postion

input :
output :

 */
void Game::Start()
{
	LoadSprites();
	head = (NODE)malloc(sizeof(struct node));
	head->posx = 0;
	head->posy = 0;
	head->direction = right;
	head->s = &TrainSprite;
	head->llink = head->rlink = NULL;
	tail = head;
	snoopy.setPosition(head->posx, head->posy);
	Score.setPosition(700, 10);
	Score.setString(sf::String(std::to_string(score + 1)));
	window.create(sf::VideoMode(800, 600), "Train", sf::Style::Titlebar | sf::Style::Close);
}

/*

Describtion :
call the function start we explin it
and the render we will exaplin but it is related to the window and sfml
input :
output :

 */
void Game::Run()
{
	Start();
	while (window.isOpen())
	{
		Render();
		processEvents();
		if (count == speed)
		{
			Update();
		}
		count++;
	}
}

/*

Describtion :
claer the window and draw the background and draw the score on the right above
while the train move it is raning and render the seen
the it draw the snoopy which the train will eat

input :no parm
output :void

 */
void Game::Render()
{
	window.clear();
	window.draw(bg);
	window.draw(Score);
	setHeadSprite(head, &TrainSprite);
	cur = head;
	while (cur != NULL)
	{
		if (cur != head)
			setTrailingSprite(cur, &TrainSprite);
		(*cur->s).setPosition(cur->posx, cur->posy);
		window.draw(*cur->s);
		cur = cur->rlink;
	}
	window.draw(snoopy);
	window.display();
}
/*
Describtion :
related to sfml tool comes with the photo from content file and map it to spriter entity
input :no parm
output :void
 */

void Game::LoadSprites()
{
	this->spriteSheet.loadFromFile("content/trainsprite.png");
	TrainSprite.setTexture(spriteSheet);
	TrainSprite.setScale(sf::Vector2f(0.25, 0.25));
	TrainSprite.setOrigin(104.5, 104.5);

	snoopy.setTexture(spriteSheet);
	snoopy.setTextureRect(sf::IntRect(size * 3, size * 1, size, size));
	snoopy.setScale(0.2, 0.2);
	snoopy.setOrigin(104.5, 104.5);

	font.loadFromFile("content/Roboto-Bold.ttf");
	Score.setFont(font);
	Score.setFillColor(sf::Color::Black);

	this->Background.loadFromFile("content/sand.jpg");
	bg.setTexture(Background);
	bg.setScale(2, 2);
}

/*

Describtion :
this function set the head depends on the direction of move
input :no parm
output :void

 */
void Game::setHeadSprite(NODE head, sf::Sprite* sp)
{
	switch (head->direction)
	{
		case up:
			sp->setTextureRect(sf::IntRect(size * 1, size * 0, size, size));
			head->s = sp;
			break;
		case down:
			sp->setTextureRect(sf::IntRect(size * 0, size * 0, size, size));
			head->s = sp;
			break;
		case left:
			sp->setTextureRect(sf::IntRect(size * 3, size * 0, size, size));
			head->s = sp;
			break;
		case right:
			sp->setTextureRect(sf::IntRect(size * 2, size * 0, size, size));
			head->s = sp;
			break;
		default:
			break;
	}
}

/*

Describtion :
decide where to add additional part depeds on the direction
input :no parm
output :void

 */
void Game::setTrailingSprite(NODE node, sf::Sprite* sp)
{
	switch (node->direction)
	{
		case up:
			sp->setTextureRect(sf::IntRect(size * 1, size * 1, size, size));
			node->s = sp;
			break;
		case down:
			sp->setTextureRect(sf::IntRect(size * 2, size * 1, size, size));
			node->s = sp;
			break;
		case left:
			sp->setTextureRect(sf::IntRect(size * 0, size * 1, size, size));
			node->s = sp;
			break;
		case right:
			sp->setTextureRect(sf::IntRect(size * 0, size * 1, size, size));
			node->s = sp;
			break;
		default:
			break;
	}
}

/*

Describtion :
process the keyboard event depends on w or s or a or d

input :no parm
output :void

 */
void Game::processEvents()
{
	if (window.pollEvent(event))
	{
		switch (event.type)
		{
			case sf::Event::Closed: window.close(); break;
			case sf::Event::KeyPressed:
				if (event.key.code == sf::Keyboard::W && head->direction != down)
				{
					head->direction = up;
				}
				else if (event.key.code == sf::Keyboard::S && head->direction != up)
				{
					head->direction = down;
				}
				else if (event.key.code == sf::Keyboard::A && head->direction != right)
				{
					head->direction = left;
				}
				else if (event.key.code == sf::Keyboard::D && head->direction != left)
				{
					head->direction = right;
				}
			default:
				break;
		}
	}
}

/*

Describtion :
claer the window and draw the background and draw the score on the right above
while the train move it is raning and render the seen
the it draw the snoopy which the train will eat

input :no parm
output :void

 */

sf::Vector2f Game::getSnoopyCoords()
{
	return sf::Vector2f((rand() % 26 + 1) * side * 2, (rand() % 19 + 1) * side * 2);
}

void Game::HandleSnoopyTouched()
{
	if (isSnoopyTouched(head, &snoopy))
	{
		head = insertHead(head, &TrainSprite);
		speed--;
		while (1)
		{
			snoopyPos = getSnoopyCoords();
			cur = head;
			while (cur != NULL)
			{
				if (cur->posx == snoopyPos.x && cur->posy == snoopyPos.y)
				{
					break;
				}
				cur = cur->rlink;
			}
			if (cur == NULL)
				break;
		}
		snoopy.setPosition(getSnoopyCoords());
		score++;
		Score.setString(sf::String(std::to_string(score)));
	}
}

/*

Describtion :
check if the postion of the head of the train is same as snoopoy it means the snoopy touched
input :no parm
output :void

 */
bool Game::isSnoopyTouched(NODE head, sf::Sprite* snoopy)
{
	return sf::Vector2f(head->posx, head->posy) == snoopy->getPosition();
}

/*

Describtion :
check if the train intersect it self to end the game

input :no parm
output :void

 */
void Game::checkIntersection(NODE head, sf::RenderWindow* window)
{
	NODE cur = head->rlink;
	while (cur != NULL)
	{
		if (head->posx == cur->posx && head->posy == cur->posy)
		{
			window->close();
		}
		cur = cur->rlink;
	}
}
