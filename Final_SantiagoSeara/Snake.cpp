#include "Snake.h"



void SnakeUpdate(Snake& snake)
{
	switch (snake.dir) // Mueve la cabeza de la serpiente según la dirección
	{
	case LEFT:
		snake.head.x--;
		break;
	case RIGHT:
		snake.head.x++;
		break;
	case UP:
		snake.head.y--;
		break;
	case DOWN:
		snake.head.y++;
		break;
	default:
		break;
	}
}
void SnakeMovement(Snake& snake)
{
	Vector2 prevPos;
	Vector2 auxPos;

	// Movimiento de la serpiente
	for (int i = 0; i < snake.nTail; i++)
	{
		if (i == 0) // Cabeza
		{
			prevPos = snake.tail[i]; // Guarda la posición actual de la cabeza
			snake.tail[i] = { snake.head }; // Mueve la cabeza a la nueva posición (head)
		}
		else
		{
			auxPos = snake.tail[i]; // Guarda la posición actual de este segmento antes de actualizarlo
			snake.tail[i] = { prevPos.x,prevPos.y }; // Mueve este segmento a la posición del segmento anterior
			prevPos = auxPos; // Actualiza prevPos con la posición original de este segmento, para el próximo ciclo
		}
	}
}
void LastTailRemoval(Snake& snake)
{
	Vector2 cursorPosition; //genero un vector2 auxiliar

	cursorPosition.x = snake.tail[snake.nTail - 1].x; // borra la ultima posicion de la serpiente
	cursorPosition.y = snake.tail[snake.nTail - 1].y;

	SetConsoleCursorPos(cursorPosition);
	cout << " ";
}
void DrawSnake(Snake snake)
{
	for (int i = 0; i < snake.nTail; i++)
	{
		SetConsoleColor(2);
		SetConsoleCursorPos(snake.tail[i]);
		if (i == 0)
		{
			cout << "O"; // Cabeza
		}
		else
		{
			cout << "o"; // Cuerpo
		}
		SetConsoleColor(15);
	}
}