#pragma once
#include "Chess.h"
#include <iostream>
#include <string>
#include <algorithm>
#include <windows.h>
using namespace std;
void Color(int a) {
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), a);
}
void SetColor(int color = 7)
{
	HANDLE hConsole;
	hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
	SetConsoleTextAttribute(hConsole, color);
}

std::string convert[14] = { "將", "士", "象", "馬", "車", "炮", "卒", "帥", "仕", "相", "馬", "車", "砲", "兵" };

class Viewer {
public:
	std::string pboard[10][9];
	void update(Board board);
	void print(Board board);
	void printPath(Board board, vector<Position> path);
	void viewerClear();
};

void Viewer::update(Board board) {
	for (int i = 0; i < 10; i++) {
		for (int j = 0; j < 9; j++) {
			//std::cout << board.b[i][j] << " ";
			if (board.b[i][j] == -1) {
				pboard[i][j] = "  ";
			}
			else {
				pboard[i][j] = convert[board.b[i][j]];
			}
		}
		//std::cout << "\n";
	}
}

void Viewer::print(Board board) {
	system("cls");
	SetColor(240);
	cout << "  |０|１|２|３|４|５|６|７|８|\n";
	for (int i = 0; i < 10; i++) {
		cout << i << " |";
		for (int j = 0; j < 9; j++) {
			if (board.b[i][j] > 6) {
				SetColor(240);
			}
			else{
				SetColor(252);
			}
			cout << pboard[i][j];
			SetColor(240);
			cout << "|";
		}
		cout << endl;
		if (i == 4) {
			SetColor(249);
			cout << "  ----------------------------\n";
			cout << "      楚    河    漢    界    \n";
			cout << "  ----------------------------\n";
		}
		SetColor(240);
	}
	SetColor(240);
	cout << endl;
}


void Viewer::viewerClear() {
	for (int i = 0; i < 10; i++) {
		for (int j = 0; j < 9; j++) {
			pboard[i][j].clear();
		}
	}
}

void Viewer::printPath(Board board, vector<Position> path) {
	system("cls");
	SetColor(240);
	cout << "  |０|１|２|３|４|５|６|７|８|\n";
	for (int i = 0; i < 10; i++) {
		cout << i << " |";
		for (int j = 0; j < 9; j++) {
			Position p = Position{ i, j };
			if (find(path.begin() + 1, path.end(), p) != path.end()) {
				if (board.b[i][j] == -1) {
					SetColor(160);
				}
				else if (board.b[path[0].y][path[0].x] > 6 && board.b[i][j] > 6) {
					SetColor(240);
				}
				else if(board.b[path[0].y][path[0].x] <= 6 && board.b[i][j] <= 6){
					SetColor(252);
				}
				else {
					if (board.b[i][j] > 6) {
						SetColor(160);
					}
					else {
						SetColor(172);
					}
				}
			}
			else if (board.b[i][j] > 6) {
				SetColor(240);
			}
			else {
				SetColor(252);
			}
			cout << pboard[i][j];
			SetColor(240);
			cout << "|";
		}
		cout << endl;
		if (i == 4) {
			SetColor(249);
			cout << "  ----------------------------\n";
			cout << "      楚    河    漢    界    \n";
			cout << "  ----------------------------\n";
		}
		SetColor(240);
	}
	SetColor(240);
	cout << endl;
}