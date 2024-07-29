#include "Menu.h"
#include "SceneManager.h"
#include "Fruit.h"
#include "Snake.h"
#include "Game.h"

void SetSpeedMode();
void Rules();
void Init();
void GameUpdate(Scenes& scene);
void CollisionDetector();
void Input();
void Draw();
void DrawBorders();
void GameOver(Scenes& scene);
void WinningPopUp(Scenes& scene);
void GameMode();
void GameModeSelector(const int& menuItems, int& currentSelection, const string  options[3], char& input);

enum class gameScenes
{
	rules,
	gameModes,
	playing,
	gameOver,
	youWin
};

const int BORDER_WIDTH = 20;
const int BORDER_HEIGHT = 20;

int score;
int normalSpeed = 150;
int speedHardMode = 80;

Snake snake;
Fruit fruit;

bool easyMode = false;
bool hardMode = false;
bool classicMode = false;
bool frenzyMode = false;

int easyModeWinScore = 150;
int hardModeWinScore = 250;
int classicModeWinScore = 3570;

gameScenes currentGameScene;

void Game(Scenes& scene)
{
	switch (currentGameScene)
	{
	case gameScenes::rules:
		Rules();
		break;
	case gameScenes::gameModes:
		GameMode();
		Init();
		break;
	case gameScenes::playing:
		GameUpdate(scene);
		Draw();
		SetSpeedMode();
		break;
	case gameScenes::gameOver:
		GameOver(scene);
		break;
	case gameScenes::youWin:
		WinningPopUp(scene);
		break;
	}
}
void SetSpeedMode()
{
	if (hardMode || frenzyMode)
	{
		Sleep(speedHardMode);
	}
	else
	{
		Sleep(normalSpeed);
	}
}
void Rules()
{
	system("CLS");
	SetConsoleColor(13);
	cout << "=================================\n";
	cout << "             Rules               \n";
	cout << "=================================\n" << endl;
	SetConsoleColor(15);

	cout << "W: Mueve la serpiente para arriba.\n";
	cout << "A: Mueve la serpiente para la \n";
	cout << "izquierda.\n";
	cout << "S: Mueve la serpiente para abajo.\n";
	cout << "D: Mueve la serpiente para la\n";
	cout << "derecha.\n\n";

	cout << "Si colisionas contra las paredes\n";
	cout << "o tu propia cola, perdes.\n\n";

	cout << "Come manzanas para conseguir\n";
	cout << "puntos, cada manzana son 10.\n\n";


	cout << "EasyMode: Juega hasta 150 puntos\n";
	cout << "en velocidad normal.\n\n";

	cout << "HardMode: Juega hasta 250 puntos\n";
	cout << "en velocidad aumentada.\n\n";

	cout << "ClassicMode: Juega hasta\n";
	cout << "completar la pantalla como en el\n";
	cout << "viejo snake en velocidad normal.\n\n";

	cout << "FrenzyMode: FRENZY!!!\n\n";

	system("pause");

	currentGameScene = gameScenes::gameModes;
}
void Init()
{
	system("CLS");

	snake.dir = UP;

	snake.head.x = BORDER_WIDTH / 2;
	snake.head.y = BORDER_HEIGHT / 2;

	SetNewPositionFruit(fruit.pos, BORDER_WIDTH, BORDER_HEIGHT, snake);

	for (int i = 0; i < snakeMaxLenght; i++) //Reinicia las posiciones de la serpiente a 0 para que no aparezca en pantalla
	{
		snake.tail[i] = { 0, 0 };
	}

	int initialTails = 4;

	snake.nTail = initialTails;

	score = 0;

	for (int i = 0; i < snake.nTail; i++)
	{
		snake.tail[i] = { snake.head.x, snake.head.y + i };
	}
}
void GameUpdate(Scenes& scene)
{
	LastTailRemoval(snake);

	Input();

	SnakeUpdate(snake);

	SnakeMovement(snake);

	CollisionDetector();

	if (hardMode && score == hardModeWinScore)
	{
		currentGameScene = gameScenes::youWin;
	}
	else if (easyMode && score == easyModeWinScore)
	{
		currentGameScene = gameScenes::youWin;
	}
	else if (classicMode && score == classicModeWinScore)
	{
		currentGameScene = gameScenes::youWin;
	}
	else if (frenzyMode && score == hardModeWinScore)
	{
		currentGameScene = gameScenes::youWin;
	}

}
void CollisionDetector()
{
	// Verifica si la serpiente se choca con su cola, lo cual termina el juego
	for (int i = 1; i < snake.nTail; i++)
	{
		if (snake.tail[i].x == snake.tail[0].x && snake.tail[i].y == snake.tail[0].y)
		{
			currentGameScene = gameScenes::gameOver;
		}
	}

	// Verifica si la serpiente se choca con las paredes
	if (snake.tail[0].x >= BORDER_WIDTH || snake.tail[0].x <= 0)
	{
		currentGameScene = gameScenes::gameOver;
	}

	if (snake.tail[0].y >= BORDER_WIDTH || snake.tail[0].y <= 0)
	{
		currentGameScene = gameScenes::gameOver;
	}
	if (snake.tail[0].x == fruit.pos.x && snake.tail[0].y == fruit.pos.y) // Verifica si la serpiente come la fruta
	{
		score += 10;
		SetNewPositionFruit(fruit.pos, BORDER_WIDTH, BORDER_HEIGHT, snake);
		snake.nTail++;
	}
}
void Input()
{
	if (_kbhit())
	{
		char input = _getch();
		switch (input)
		{
		case 'A':
		case 'a':
			if (snake.dir != RIGHT)
			{
				snake.dir = LEFT;
			}
			break;
		case 'D':
		case 'd':
			if (snake.dir != LEFT)
			{
				snake.dir = RIGHT;
			}
			break;
		case 'W':
		case 'w':
			if (snake.dir != DOWN)
			{
				snake.dir = UP;
			}
			break;
		case 'S':
		case 's':
			if (snake.dir != UP)
			{
				snake.dir = DOWN;
			}
			break;
		case 'X':
		case 'x':
			currentGameScene = gameScenes::gameOver;
			break;
		}
	}
}
void Draw()
{
	DrawSnake(snake);

	DrawFruits(fruit.pos);

	DrawBorders();

}
void DrawBorders()
{
	for (int i = 0; i <= BORDER_WIDTH; i++) // Bordes
	{
		int randomColor = rand() % 11 + 1;
		int colorBlue = 9;
		int colorRed = 12;
		int colorGray = 8;

		if (easyMode)
		{
			SetConsoleColor(colorBlue);
		}
		else if (hardMode)
		{
			SetConsoleColor(colorRed);
		}
		else if (classicMode)
		{
			SetConsoleColor(colorGray);
		}
		else if (frenzyMode)
		{
			SetConsoleColor(randomColor);
		}

		SetConsoleCursorPos({ i,0 });
		cout << char(219);
		SetConsoleCursorPos({ i,BORDER_HEIGHT });
		cout << char(219);
		SetConsoleCursorPos({ 0,i });
		cout << char(219);
		SetConsoleCursorPos({ BORDER_WIDTH,i });
		cout << char(219);
	}
	SetConsoleColor(15);
	SetConsoleCursorPos({ 0,BORDER_HEIGHT + 1 });
	cout << "Score: " << score;
}
void GameOver(Scenes& scene)
{
	hardMode = false;
	easyMode = false;
	classicMode = false;

	int gameOverTextX = BORDER_WIDTH / 4 + 1;
	int gameOverTextY = BORDER_HEIGHT / 2;
	int returnToMenuTextX = BORDER_WIDTH / 4 - 1;
	int returnToMenuTextY = BORDER_HEIGHT / 2 + 3;
	int retryTextX = BORDER_WIDTH / 4 - 2;
	int retryTextY = BORDER_HEIGHT / 2 + 4;

	SetConsoleColor(12);
	SetConsoleCursorPos({ gameOverTextX, gameOverTextY });
	cout << "GAME OVER";
	SetConsoleColor(15);
	SetConsoleCursorPos({ returnToMenuTextX, returnToMenuTextY });
	cout << "'Q' to menu..";
	SetConsoleCursorPos({ retryTextX, retryTextY });
	cout << "'E' to retry...";

	if (_kbhit())
	{
		char input = _getch();
		switch (input)
		{
		case 'Q':
		case 'q':
			scene = Scenes::menu;
		case 'e':
		case 'E':
			currentGameScene = gameScenes::rules;
			break;
		default:
			break;
		}
	}
}
void WinningPopUp(Scenes& scene)
{
	hardMode = false;
	easyMode = false;
	classicMode = false;

	int winTextX = BORDER_WIDTH / 2 - 3;
	int winTextY = BORDER_HEIGHT / 2;
	int returnToMenuTextX = BORDER_WIDTH / 4 - 1;
	int returnToMenuTextY = BORDER_HEIGHT / 2 + 3;
	int retryTextX = BORDER_WIDTH / 4 - 2;
	int retryTextY = BORDER_HEIGHT / 2 + 4;

	SetConsoleColor(10);
	SetConsoleCursorPos({ winTextX, winTextY });
	cout << "YOU WIN";
	SetConsoleColor(15);
	SetConsoleCursorPos({ returnToMenuTextX, returnToMenuTextY });
	cout << "'Q' to menu..";
	SetConsoleCursorPos({ retryTextX, retryTextY });
	cout << "'E' to retry...";


	if (_kbhit())
	{
		char input = _getch();
		switch (input)
		{
		case 'q':
		case 'Q':
			scene = Scenes::menu;
		case 'e':
		case 'E':
			currentGameScene = gameScenes::rules;
			break;
		default:
			break;
		}
	}
}
void GameMode()
{
	char input;
	int currentSelection = 0;  // Variable para almacenar la selección actual del menú
	const int menuItems = 4;  // Número total de opciones del menú

	// Opciones de menú para mostrar
	const string options[menuItems] = { "Easy Mode", "Hard Mode", "Classic", "FRENZY" };


	do {
		system("cls");  // Limpia la pantalla
		SetConsoleColor(13);
		cout << "=================================\n";
		cout << "         Select Game Mode        \n";
		cout << "=================================\n" << endl;
		SetConsoleColor(15);
		GameModeSelector(menuItems, currentSelection, options, input);
	} while (input != 13);  // 13 es el código ASCII para Enter

	// Devuelve la opción seleccionada basada en currentSelection
	switch (currentSelection)
	{
	case 0:
		easyMode = true;
		break;
	case 1:
		hardMode = true;
		break;
	case 2:
		classicMode = true;
		break;
	case 3:
		frenzyMode = true;
	default:
		break;
	}
	currentGameScene = gameScenes::playing;
}
void GameModeSelector(const int& menuItems, int& currentSelection, const string  options[3], char& input)
{
	for (int i = 0; i < menuItems; i++)
	{
		if (i == currentSelection)
		{
			if (i == 0)
			{
				SetConsoleColor(11);
				SetConsoleColor(15);
			}
			else if (i == 1)
			{
				SetConsoleColor(12);
				SetConsoleColor(15);
			}
			else
			{
				SetConsoleColor(15);
			}
			cout << "           " << "> " << options[i] << " <" << endl;  // Resalta la opción seleccionada
		}
		else
		{
			cout << "             " << options[i] << endl;
		}
	}

	input = _getch();  // Lee que se haya apretado un boton

	// Navegación del menú basada en la entrada de las flechas
	switch (input) {
	case 'w':
	case 'W':// si apreto w
		currentSelection = (currentSelection + menuItems - 1) % menuItems; // Actualiza la selección actual del menú. Decrementa la selección y utiliza el módulo para garantizar que el índice se mantenga dentro de los límites válidos, permitiendo un desplazamiento circular hacia arriba.
		break;
	case 's':
	case 'S':// si apreto s
		currentSelection = (currentSelection + 1) % menuItems;
		break;
	case '\r':  // Enter también funciona para seleccionar. '\r' representa el "Carriage Return", que se utiliza comúnmente para detectar cuando se presiona Enter en consolas.
		input = 13;  // Configura input a 13 para salir del bucle
		break;
	}
}