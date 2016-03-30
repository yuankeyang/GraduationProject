#include <iostream>
#include <Windows.h>
#include <iomanip>
#include <string>


using namespace std;

int main()
{
	std::string str1 = "will not see this";
	std::string str2 = "\rdsgagd";
	str2.append("sdafds");
	std::cout << str1 << std::flush;
	std::cout << str2;
	std::cout << std::endl; // all done
	string str = "Hello!";
	cout << std::left << std::setw(18) << str;
	cout << std::left << std::setw(18) << "\rte";
	HANDLE hConsole;
	hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
	COORD coord;
	coord.X = 4;
	coord.Y = 5;
	for (int k = 1; k < 255; k++)
	{
		SetConsoleCursorPosition(hConsole, coord);
		SetConsoleTextAttribute(hConsole, k);
		cout << "Hello World" << endl;
	}
	system("pause");
	return EXIT_SUCCESS;
}