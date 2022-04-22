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
