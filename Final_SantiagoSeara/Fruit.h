#pragma once
#include "Utilities.h"
#include "Snake.h"

struct Fruit
{
	Vector2 pos;
};
void SetNewPositionFruit(Vector2& fruitPos, int width, int height, Snake& snake);
void DrawFruits(Vector2& fruitPos);