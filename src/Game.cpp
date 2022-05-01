#include "Game.h"
#include <SFML/Graphics.hpp>
#include <iostream>
#define side 15
#define size 208.5

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

NODE Game::deleteTail(NODE tail)
{
	NODE temp;
	temp = tail->llink;
	temp->rlink = NULL;
	free(tail);
	tail = NULL;
	return temp;
}

void Game::Update()
{
	if (head1->posx > 810)
		head1->posx = 0;
	if (head1->posx < 0)
		head1->posx = 810;
	if (head1->posy > 600)
		head1->posy = 0;
	if (head1->posy < 0)
		head1->posy = 600;
	/////// head2
	if (head2->posx > 810)
		head2->posx = 0;
	if (head2->posx < 0)
		head2->posx = 810;
	if (head2->posy > 600)
		head2->posy = 0;
	if (head2->posy < 0)
		head2->posy = 600;
	HandleSnoopyTouched();
	//head1
	head1 = insertHead(head1, &TrainSprite1);
	tail1 = deleteTail(tail1);
	checkIntersection(head1, &window);

	//// head2
	head2 = insertHead(head2, &TrainSprite2);
	tail2 = deleteTail(tail2);
	checkIntersection(head2, &window);
	count1 = 0;
	count2 = 0;
}

void Game::Start()
{
	LoadSprites();

	head1 = (NODE)malloc(sizeof(struct node));
	head2 = (NODE)malloc(sizeof(struct node));

	head1->posx = 0;
	head1->posy = 0;
	head1->direction = right;
	head1->s = &TrainSprite1;
	head1->llink = head1->rlink = NULL;
	tail1 = head1;
	////// for two
	head2->posx = 100;
	head2->posy = 100;
	head2->direction = down;
	head2->s = &TrainSprite2;
	head2->llink = head2->rlink = NULL;
	tail2 = head2;
	////
	snoopy.setPosition(head1->posx, head1->posy);
	////
	Score1.setPosition(700, 10);
	Score1.setString(sf::String(std::to_string(score1 + 1)));
	///////////
	Score2.setPosition(700, 50);
	Score2.setString(sf::String(std::to_string(score2 + 1)));
	/////////
	window.create(sf::VideoMode(800, 600), "Train", sf::Style::Titlebar | sf::Style::Close);
}

void Game::Run()
{
	Start();
	while (window.isOpen())
	{
		Render();
		processEvents();
		if (count1 == speed1)
		{
			Update();
		}
		count1++;
	}
}

void Game::Render()
{
	window.clear();
	window.draw(bg);
	window.draw(Score1);
	window.draw(Score2);

	// cur1 = head1;
	// while (cur1 != NULL)
	// {
	// 	if (cur1 != head1)
	// 		setTrailingSprite(cur1, &TrainSprite1);
	// 	(*cur1->s).setPosition(cur1->posx, cur1->posy);
	// 	window.draw(*cur1->s);
	// 	cur1 = cur1->rlink;
	// }
	///////
	setHeadSprite(head1, &TrainSprite1);
	setHeadSprite(head2, &TrainSprite2);
	cur1 = head1;
	cur2 = head2;
	while ((cur1 != NULL) | (cur2 != NULL))
	{
		if (cur1 != NULL)
		{
			if (cur1 != head1)
				setTrailingSprite(cur1, &TrainSprite1);
			(*cur1->s).setPosition(cur1->posx, cur1->posy);
			window.draw(*cur1->s);
			cur1 = cur1->rlink;
		}

		if (cur2 != NULL)
		{
			if (cur2 != head2)
				setTrailingSprite(cur2, &TrainSprite2);
			(*cur2->s).setPosition(cur2->posx, cur2->posy);
			window.draw(*cur2->s);
			cur2 = cur2->rlink;
		}
	}
	window.draw(snoopy);
	window.display();
}
void Game::LoadSprites()
{
	this->spriteSheet1.loadFromFile("content/trainsprite1.png");
	TrainSprite1.setTexture(spriteSheet1);
	TrainSprite1.setScale(sf::Vector2f(0.25, 0.25));
	TrainSprite1.setOrigin(104.5, 104.5);
	///////////
	this->spriteSheet2.loadFromFile("content/trainsprite2.png");
	TrainSprite2.setTexture(spriteSheet2);
	TrainSprite2.setScale(sf::Vector2f(0.25, 0.25));
	TrainSprite2.setOrigin(104.5, 104.5);
	////////

	snoopy.setTexture(spriteSheet1);
	snoopy.setTextureRect(sf::IntRect(size * 3, size * 1, size, size));
	snoopy.setScale(0.2, 0.2);
	snoopy.setOrigin(104.5, 104.5);

	font1.loadFromFile("content/Roboto-Bold.ttf");
	Score1.setFont(font1);
	Score1.setFillColor(sf::Color::Black);
	////////
	font2.loadFromFile("content/Roboto-Bold.ttf");
	Score2.setFont(font2);
	Score2.setFillColor(sf::Color::Red);

	this->Background.loadFromFile("content/sand.jpg");
	bg.setTexture(Background);
	bg.setScale(2, 2);
}

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

void Game::processEvents()
{
	if (window.pollEvent(event))
	{
		switch (event.type)
		{
			case sf::Event::Closed: window.close(); break;
			case sf::Event::KeyPressed:
				if (event.key.code == sf::Keyboard::W && head1->direction != down)
				{
					head1->direction = up;
				}
				if (event.key.code == sf::Keyboard::S && head1->direction != up)
				{
					head1->direction = down;
				}
				if (event.key.code == sf::Keyboard::A && head1->direction != right)
				{
					head1->direction = left;
				}
				if (event.key.code == sf::Keyboard::D && head1->direction != left)
				{
					head1->direction = right;
				}
				//// hnadle second event
				if (event.key.code == sf::Keyboard::Down && head2->direction != up)
				{
					head2->direction = down;
				}
				if (event.key.code == sf::Keyboard::Left && head2->direction != right)
				{
					head2->direction = left;
				}
				if (event.key.code == sf::Keyboard::Right && head2->direction != left)
				{
					head2->direction = right;
				}
				if (event.key.code == sf::Keyboard::Up && head2->direction != down)
				{
					head2->direction = up;
				}
			default:
				break;
		}
	}
}

sf::Vector2f Game::getSnoopyCoords()
{
	return sf::Vector2f((rand() % 26 + 1) * side * 2, (rand() % 19 + 1) * side * 2);
}

void Game::HandleSnoopyTouched()
{
	if (isSnoopyTouched(head2, &snoopy))
	{
		head2 = insertHead(head2, &TrainSprite2);
		speed2--;
		while (1)
		{
			snoopyPos = getSnoopyCoords();
			cur2 = head2;
			while (cur2 != NULL)
			{
				if (cur2->posx == snoopyPos.x && cur2->posy == snoopyPos.y)
				{
					break;
				}
				cur2 = cur2->rlink;
			}
			if (cur2 == NULL)
				break;
		}

		snoopy.setPosition(getSnoopyCoords());
		score2++;
		Score2.setString(sf::String(std::to_string(score2)));
	}
	if (isSnoopyTouched(head1, &snoopy))
	{
		head1 = insertHead(head1, &TrainSprite1);
		speed1--;
		while (1)
		{
			snoopyPos = getSnoopyCoords();
			cur1 = head1;
			while (cur1 != NULL)
			{
				if (cur1->posx == snoopyPos.x && cur1->posy == snoopyPos.y)
				{
					break;
				}
				cur1 = cur1->rlink;
			}
			if (cur1 == NULL)
				break;
		}
		snoopy.setPosition(getSnoopyCoords());
		score1++;
		Score1.setString(sf::String(std::to_string(score1)));
	}
}

bool Game::isSnoopyTouched(NODE head, sf::Sprite* snoopy)
{
	return sf::Vector2f(head->posx, head->posy) == snoopy->getPosition();
}

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
