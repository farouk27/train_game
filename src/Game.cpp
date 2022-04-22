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
