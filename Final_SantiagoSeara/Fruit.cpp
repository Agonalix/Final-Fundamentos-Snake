#include "Fruit.h"

void DrawFruits(Vector2& fruitPos)
{
	SetConsoleColor(12);
	SetConsoleCursorPos({ fruitPos });//fruta
	cout << "*";
	SetConsoleColor(15);
}
void SetNewPositionFruit(Vector2& fruitPos, int width, int height, Snake& snake)
{
	fruitPos.x = 2 + rand() % (width - 2); // Genera de 2 a 19
	fruitPos.y = 2 + rand() % (height - 2); // Genera de 2 a 19

	for (int i = 0; i < snake.nTail; i++)
	{
		if (fruitPos.x == snake.tail[i].x && fruitPos.y == snake.tail[i].y)
		{
			fruitPos.x = 2 + rand() % (width - 2);
			fruitPos.y = 2 + rand() % (height - 2);
		}
	}
}