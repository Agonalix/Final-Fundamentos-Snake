#pragma once
#include "Utilities.h"

const int snakeMaxLenght = 400;

enum eDirection { STOP = 0, LEFT, RIGHT, UP, DOWN };

struct Snake
{
	Vector2 tail[snakeMaxLenght];
	Vector2 head;
	int nTail;
	eDirection dir;
};

void SnakeUpdate(Snake& snake);
void SnakeMovement(Snake& snake);
void LastTailRemoval(Snake& snake);
void DrawSnake(Snake snake);