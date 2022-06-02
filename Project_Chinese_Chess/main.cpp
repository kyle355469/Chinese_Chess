#include "GameManager.h"
#include <iostream>
#include <fstream>
#include <Windows.h>

int startPage();

int main() {
	HWND console = GetConsoleWindow();
	RECT r;
	GetWindowRect(console, &r); 
	MoveWindow(console, r.left, r.top, 550, 350, TRUE);
	
	SetColor(240);
	while (true) {
		int inputType = startPage();
		if (inputType == 1) {
			//MoveWindow(console, r.left, r.top, 320, 500, TRUE);
			system("cls");
			GameManager gm;
			gm.play();
			std::cout << "\n\n";
			std::cout << "輸入1回到主畫面,\n";
			std::cout << "輸入-1結束程式:\n";
			std::cin >> inputType;
			if (inputType == -1) {
				break;
			}
		}
		else if (inputType == 2) {
			system("cls");
			FileGameManager fgm;
			fgm.play();
		}
		else if (inputType == -1) {
			break;
		}
	}
}

int startPage() {
	system("cls");
	int inputType;
	cout << "  __          _____           _____   ___   _____\n";
	cout << " /    |    |    |    | \\   |  |      /   \\  |\n";
	cout << "|     |====|    |    |  \\  |  |----  \\___   |----\n";
	cout << "|     |    |    |    |   \\ |  |          \\  |\n";
	cout << " \\__  |    |  __|__  |    \\|  |____  \\___/  |____\n\n";
	cout << "                        __           _____   ___    ___\n";
	cout << "                       /    |    |   |      /   \\  /   \\\n";
	cout << "                      |     |====|   |----  \\___   \\___\n";
	cout << "                      |     |    |   |          \\      \\\n";
	cout << "                       \\__  |    |   |____  \\___/  \\___/\n";
	cout << "===========================================================\n";
	cout << "                   Please choose the mode\n";
	cout << "                        1.input mode\n";
	cout << "                      2.read-file mode\n";
	cout << "                          -1.exit\n";
	cout << "                             ";
	while (cin >> inputType) {
		if (inputType != 1 && inputType != 2 && inputType != -1) {
			cout << "                       inValid input!\n";
			cout << "                             ";
			continue;
		}
		else {
			return inputType;
		}
	}
} 