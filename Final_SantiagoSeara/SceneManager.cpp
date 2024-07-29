#include "Game.h"
#include "Menu.h"

void UpdateProgram();
void InitProgram();

Scenes scene;

Vector2 menuSize = { 64, 30 };

void RunProgram()
{
	InitProgram();
	while (scene != Scenes::exit)
	{
		UpdateProgram();
	}
}

void InitProgram()
{
	HideCursor();
	srand(time(nullptr)); //vacio de memoria
	scene = Scenes::menu;
}

void UpdateProgram()
{
	switch (scene)
	{
	case Scenes::menu:
		SetConsoleSize(menuSize.x, menuSize.y);
		ShowMenu(scene);
		break;
	case Scenes::game:
		Game(scene);
		break;
	case Scenes::credits:
		Credits(scene);
		break;
	case Scenes::exit:
		exit(NULL);
		break;
	}
}