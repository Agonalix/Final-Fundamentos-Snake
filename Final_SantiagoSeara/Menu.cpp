#include "Menu.h"

void MenuSelector(const int& menuItems, int& currentSelection, const std::string  options[3], char& input);
void ImagePrint();
void ShowMenu(Scenes& scene)
{
	system("CLS");
	char input;
	int currentSelection = 0;  // Variable para almacenar la selección actual del menú
	const int menuItems = 3;  // Número total de opciones del menú

	// Opciones de menú para mostrar
	const string options[menuItems] = { "Start Game", "Credits", "Exit" };

	// Bucle para manejar la navegación del menú
	do {
		system("cls");  // Limpia la pantalla
		ImagePrint();

		MenuSelector(menuItems, currentSelection, options, input);
	} while (input != 13);  // 13 es el código ASCII para Enter

	// Devuelve la opción seleccionada basada en currentSelection
	switch (currentSelection)
	{
	case 0:
		scene = Scenes::game;
		break;
	case 1:
		scene = Scenes::credits;
		break;
	case 2:
		scene = Scenes::exit;
		break;
	default:
		break;
	}
}
void MenuSelector(const int& menuItems, int& currentSelection, const std::string  options[3], char& input)
{
	for (int i = 0; i < menuItems; i++)
	{
		if (i == currentSelection)
		{
			cout << "                         " << "> " << options[i] << " <" << endl;  // Resalta la opción seleccionada
		}
		else
		{
			cout << "                           " << options[i] << endl;
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
void ImagePrint()
{
	SetConsoleColor(2);
	cout << R"(::::::::::::::::::::::::::::::::::::;;+++++++;::::::::::::::::::)" << endl;
	cout << R"(::::::::::::::::::::::::::::::::;*?%%????*??%SS?+:::::::::::::::)" << endl;
	cout << R"(:::::::::::::::::::::::::::::;*%%?*+;;;;;+%%*+*%S%*:::::::::::::)" << endl;
	cout << R"(:::::::::::::::::::::::::::;?S?+;;;;+++++*SS?+++*%#?::::::::::::)" << endl;
	cout << R"(::::::::::::::::::::::::::*#?:;;+++++**??????????S#*::::::::::::)" << endl;
	cout << R"(:::::::::::::::::::::::::*#%;:++++*?%SS%%%%%%%%%%?+:::::;+*??;::)" << endl;
	cout << R"(::::::::::::::::::::::::;#S+;+++**%#%+:::::::::::::;**+*%%%#%:::)" << endl;
	cout << R"(::::::::::::::::::::::::+#%+++++**##;::::::::::::::;+?S#SSS?::::)" << endl;
	cout << R"(:::::;;:::::::::::::::::;#S**+++**%#?::::::::::::;*?%%SSSSS%?+::)" << endl;
	cout << R"(:::+%#%::::::::::::::::::?#%**++***%#S*;::::::::+S%*+?????%S##?:)" << endl;
	cout << R"(::*###%::::::::::;;;;;;;;;?#S?*******%SS?;:::::;SS*;?%%%%%%%SS#*)" << endl;
	cout << R"(:+#S?S#*::::;*?%%%%%%%%%%%%%S#S?*******?SS%+:::;SS?*%%%%%%%%S##*)" << endl;
	cout << R"(:?#%?*%#%**%S%**+++++++++++++*%SS%?******?%#%+::*##S%%%%SSSS##?:)" << endl;
	cout << R"(:+#S??**S#S%*****************??%###%?******?##*::;?S#######S%+::)" << endl;
	cout << R"(::?#S%?%#S?******?%SSSSSSSSSSSS%*;+SS??*****?##+:::;++***++;::::)" << endl;
	cout << R"(:::+%#S##%******?S#*+++++++++;;::::+#S******?S#?::::::::::::::::)" << endl;
	cout << R"(:::::+*S#%?*****?S#*;:::::::::::::;?#%******?S#?::::::::::::::::)" << endl;
	cout << R"(::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::)" << endl;
	cout << R"(:;*?%%?*;:::+??+::::;??;::::::;??+::::::;*?+::::+?%+::;*???????+)" << endl;
	cout << R"(+S#S*?%S*:::%###?;::+##*:::::+S###+:::::+##?:;*%#S*;::+##S?????+)" << endl;
	cout << R"(*##S?*+;::::?#####?;+##*::::+S#?%##+::::+##?*S#%+:::::+##S****+:)" << endl;
	cout << R"(:;*?%S##%;::?##+*S#S%##*:::;S##**###+:::+######%+:::::+##S%%%%+:)" << endl;
	cout << R"(+??*++%##;::%##;:;?S###?::;S#S%%%%S##+::+##S*;?S#S*;::+##%++++*+)" << endl;
	cout << R"(;?%SSS%?;:::*S%;:::;?S%+::*S?;::::;%S?::;SS+:::;*SS+::;%%%SSSS%*)" << endl;
	SetConsoleColor(13);

	cout << "================================================================\n";
	SetConsoleColor(15);
}
void Credits(Scenes& scene)
{
	system("CLS");

	SetConsoleColor(13);
	cout << "=================================\n";
	cout << "            Credits              \n";
	cout << "=================================\n" << endl;
	SetConsoleColor(15);

	cout << "Creador: Santiago Seara\n";
	cout << "Institucion: Image Campus\n" << endl;
	cout << "Itch.io: https://agonalix.itch.io\n";
	cout << "E-mail: santiago.seara853@gmail.com\n" << endl;

	system("PAUSE");
	scene = Scenes::menu;
}