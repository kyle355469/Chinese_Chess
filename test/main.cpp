#include <iostream>
#include <fstream>
using namespace std;

int main() {
	fstream f;
	f.open("test.txt", ios::in);
	string getStr1;
	string getStr2;
	string getStr3;
	char getCharaa;
	string getStr5;
	char getChar1;
	char getChar2;
	char getChar3;
	char getChar4;
	char getChar5;
	char getChar6;
	char getChar7;
	int playerCheck = 0;
	int chooseX = 0, chooseY = 0, toX = 0, toY = 0;
//Player: 1, Action: Soldier (6, 6) -> (6, 5)
	f >> getStr1 >> playerCheck >> getChar1 >> getStr2 >> getStr3 >> getCharaa
		>> chooseX >> getChar3 >> chooseY >> getChar4 >> getStr5
		>> getChar5 >> toX >> getChar6 >> toY >> getChar7;
	cout << getStr1 << " " << playerCheck << " " << getChar1 << " " << getStr2 << " "  << getStr3 << " " << getCharaa
		<< " " << chooseX << " " << getChar3 << " " << chooseY << " " << getChar4 << " " << getStr5
		<< " " << getChar5 << " " << toX << " " << getChar6 << " " << toY << " " << getChar7;
	return 0;
}
