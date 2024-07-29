#include "Utilities.h"

void SetConsoleCursorPos(Vector2 pos) // posiciona el cursor en un vector2 especifico anteriormente escrito. Funcion creada en base a windows.h
{
	HANDLE handle = GetStdHandle(STD_OUTPUT_HANDLE);
	SetConsoleCursorPosition(handle, { static_cast<short>(pos.x), static_cast<short>(pos.y) });
}
void HideCursor()
{
	CONSOLE_CURSOR_INFO cursorInfo;
	cursorInfo.dwSize = 100;
	cursorInfo.bVisible = FALSE;

	SetConsoleCursorInfo(GetStdHandle(STD_OUTPUT_HANDLE), &cursorInfo);
}
void SetConsoleColor(int colorCode)
{
	HANDLE handle = GetStdHandle(STD_OUTPUT_HANDLE);
	SetConsoleTextAttribute(handle, colorCode);
}
// Función para configurar el tamaño de la ventana de la consola
void SetConsoleSize(int width, int height)
{
	// Obtiene el manejador de la consola
	HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);

	// Ajusta el tamaño del buffer de la consola
	COORD bufferSize;
	bufferSize.X = width;
	bufferSize.Y = height;
	SetConsoleScreenBufferSize(hConsole, bufferSize);

	// Ajusta el tamaño de la ventana de la consola
	SMALL_RECT windowSize;
	windowSize.Left = 0;
	windowSize.Top = 0;
	windowSize.Right = width - 1;
	windowSize.Bottom = height - 1;
	SetConsoleWindowInfo(hConsole, TRUE, &windowSize);
}