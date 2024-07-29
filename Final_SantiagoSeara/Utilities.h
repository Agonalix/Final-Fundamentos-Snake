#pragma once
#include <iostream>
#include <conio.h>
#include "Vector2.h"
#include "Scenes.h"
#include "windows.h"

using namespace std;

void SetConsoleCursorPos(Vector2 pos);
void HideCursor();
void SetConsoleColor(int colorCode);
void SetConsoleSize(int width, int height);