#pragma once
#include "Chess.h"
#include "Viewer.h"
#include <iostream>
#include <vector>
#include <fstream>
using namespace std;
enum name {
	將, 士, 象, 馬, 車, 炮, 卒,
	帥, 仕, 相, 马, 俥, 砲, 兵,
};

enum name red[] = { 將 ,士 ,象 ,馬 ,車 ,炮 ,卒 , }; //true
enum name black[] = { 帥 ,仕 ,相 ,馬 ,俥 ,砲 ,兵 , }; //false

class GameManager {
public:
	std::vector<Chess*> on_board;
	bool current_player;
	Board board;
	Viewer viewer;
	int ff = -1;  // -1 沒投降，0 將投降， 1 帥投降

public:
	GameManager();
	void initialize();
	void play();
	bool checkPlayer(int x, int y);
	Chess* find(int x, int y);
	bool judge();
	bool check(bool player, Board B);					//將軍
	bool generalDied(bool player);						//將死
	bool stalemate(bool player, Board B);				//欠行
	bool faceToFace(Board B);	//王見王
};

GameManager::GameManager() {
	current_player = 0;
	//memset(board.b, ' ', 90);
}

void GameManager::initialize() {
	ff = -1;
	on_board.clear();
	board.restart();
	viewer.viewerClear();
	Chess* r1 = new General({ 0, 4 }, 0), *b1 = new General({ 9, 4 }, 1);
	Chess* r2 = new Advisor({ 0, 3 }, 0), *r3 = new Advisor({ 0, 5 }, 0);
	Chess* b2 = new Advisor({ 9, 3 }, 1), *b3 = new Advisor({ 9, 5 }, 1);
	//cout << r2.getID() << "\n";
	on_board.push_back(r1);
	on_board.push_back(b1);
	on_board.push_back(r2);
	on_board.push_back(r3);
	on_board.push_back(b2);
	on_board.push_back(b3);
	Chess* r4 = new Elephant({ 0, 2 }, 0);
	Chess* r5 = new Elephant({ 0, 6 }, 0);
	Chess* b4 = new Elephant({ 9, 2 }, 1);
	Chess* b5 = new Elephant({ 9, 6 }, 1);
	on_board.push_back(r4);
	on_board.push_back(r5);
	on_board.push_back(b4);
	on_board.push_back(b5);
	Chess* r6 = new Horse({ 0, 1 }, 0);
	Chess* r7 = new Horse({ 0, 7 }, 0);
	Chess* b6 = new Horse({ 9, 1 }, 1);
	Chess* b7 = new Horse({ 9, 7 }, 1);
	on_board.push_back(r6);
	on_board.push_back(r7);
	on_board.push_back(b6);
	on_board.push_back(b7);
	Chess* r8 = new Chariot({ 0, 0 }, 0);
	Chess* r9 = new Chariot({ 0, 8 }, 0);
	Chess* b8 = new Chariot({ 9, 0 }, 1);
	Chess* b9 = new Chariot({ 9, 8 }, 1);
	on_board.push_back(r8);
	on_board.push_back(r9);
	on_board.push_back(b8);
	on_board.push_back(b9);
	Chess* r10 = new Cannon({ 2, 1 }, 0);
	Chess* r11 = new Cannon({ 2, 7 }, 0);
	Chess* b10 = new Cannon({ 7, 1 }, 1);
	Chess* b11 = new Cannon({ 7, 7 }, 1);
	on_board.push_back(r10);
	on_board.push_back(r11);
	on_board.push_back(b10);
	on_board.push_back(b11);
	Chess* r12 = new Soldier({ 3, 0 }, 0);
	Chess* r13 = new Soldier({ 3, 2 }, 0);
	Chess* r14 = new Soldier({ 3, 4 }, 0);
	Chess* r15 = new Soldier({ 3, 6 }, 0);
	Chess* r16 = new Soldier({ 3, 8 }, 0);
	Chess* b12 = new Soldier({ 6, 0 }, 1);
	Chess* b13 = new Soldier({ 6, 2 }, 1);
	Chess* b14 = new Soldier({ 6, 4 }, 1);
	Chess* b15 = new Soldier({ 6, 6 }, 1);
	Chess* b16 = new Soldier({ 6, 8 }, 1);
	on_board.push_back(r12);
	on_board.push_back(r13);
	on_board.push_back(r14);
	on_board.push_back(r15);
	on_board.push_back(r16);
	on_board.push_back(b12);
	on_board.push_back(b13);
	on_board.push_back(b14);
	on_board.push_back(b15);
	on_board.push_back(b16);
	for (int i = 0; i < on_board.size(); i++) {
		board.b[on_board[i]->p.y][on_board[i]->p.x] = on_board[i]->id;
		//cout << on_board[i]->p.y << " " << on_board[i]->p.x << "\n";
	}
	viewer.update(board);
}

void GameManager::play() {
	initialize();
	viewer.update(board);
	viewer.print(board);
	while (true) {
		std::string input;
		int chooseX, chooseY;
		cout << "player" << current_player;
		cout << "，請輸入欲移動的棋子座標(輸入15ff投降): ";
		while (cin >> input) {
			if (input == "15ff") {
				if (current_player) {
					std::cout << "1\n";
					ff = 1;
					for (int i = 0; i < 10; i++) {
						for (int j = 0; j < 9; j++) {
							if (this->board.b[i][j] == 7) {
								this->board.b[i][j] = -1;
							}
						}
					}
				}
				else {
					std::cout << "2\n";
					ff = 0;
					for (int i = 0; i < 10; i++) {
						for (int j = 0; j < 9; j++) {
							if (this->board.b[i][j] == 0) {
								this->board.b[i][j] = -1;
							}
						}
					}
				}
				break;
			}
			else {
				cin >> chooseY;
				chooseX = stoi(input);
				if (chooseX < 9 && chooseX > -1 && chooseY < 10 && chooseY > -1) {
					if (board.b[chooseY][chooseX] == -1) {
						cout << "此位置無棋子，請重新輸入: ";
					}
					else if (checkPlayer(chooseX, chooseY)) {
						cout << "非你的棋子，請重新輸入: ";
					}
					else {
						break;
					}
				}
				else {
					cout << "已超出棋盤範圍，起重新輸入: ";
				}
			}
		}
		if (ff == -1) {
			Chess* tmp = find(chooseX, chooseY);
			/*
			vector<Position> step;
			step.clear();
			for (int i = 0; i < 10; i++) {
				for (int j = 0; j < 9; j++) {
					if ((tmp->move(board, Position{ i, j }))) {
						if (tmp->id == 0 || tmp->id == 7) {
							Board t = this->board;
							t.b[i][j] = t.b[chooseY][chooseX];
							t.b[chooseY][chooseX] = -1;
							if (!faceToFace(t)) {
								step.push_back(Position{ i, j });
								std::cout << "can move :" << j << " " << i << "\n";
							}
						}
						else
						{
							step.push_back(Position{ i, j });
							std::cout << "can move :" << j << " " << i << "\n";
						}
					}
				}
			}
			*/
			vector<Position> step = tmp->canGo();
			for (int i = 1; i < step.size(); i++) {
				if (!(tmp->move(board, step[i]))) {
					step.erase(step.begin() + i);
					i--;
				}
				Board t = this->board;
				if (tmp->id == 0 || tmp->id == 7) {
					t.b[step[i].y][step[i].x] = t.b[chooseY][chooseX];
					t.b[chooseY][chooseX] = -1;
					if (faceToFace(t)) {
						step.erase(step.begin() + i);
						i--;
					}
				}
			}
			
			viewer.printPath(board, step);
			/*
			for (auto output : step) {
				std::cout << "output:　" << output.x << " " << output.y << "\n";
			}
			*/
			/*
			if (step.size() == 0) {
				current_player = !current_player;
				std::cout << "此棋子無步可走，請重新選擇: ";
				continue;
			}
			*/
			int toX, toY;
			cout << "player" << current_player;
			cout << "，請輸入欲移動到的座標(輸入-1返回選擇棋子): ";
			while (cin >> toX) {
				if (toX == -1) {
					current_player = !current_player;
					break;
				}
				else {
					cin >> toY;
					bool again = false;
					if (!(tmp->move(board, Position{ toY, toX }))) {
						cout << "輸入的座標不可達，請重新輸入: ";
					}
					else {
						Board t = this->board;
						if (tmp->id == 0 || tmp->id == 7) {
							t.b[toY][toX] = t.b[chooseY][chooseX];
							t.b[chooseY][chooseX] = -1;
						}
						if (faceToFace(t)) {
							cout << "輸入的座標不可達，請重新輸入: ";
							again = true;
						}
						else {
							if (board.b[toY][toX] == -1) {
								board.b[toY][toX] = board.b[chooseY][chooseX];
								board.b[chooseY][chooseX] = -1;
								tmp->setPosition(toX, toY);
							}
							else {
								for (int it = 0; it != on_board.size(); it++) {
									if (on_board[it]->getPosition().x == toX && on_board[it]->getPosition().y == toY) {
										if (on_board[it]->type != tmp->type) {
											tmp->p.x = toX;
											tmp->p.y = toY;
											on_board.erase(on_board.begin() + it);
											board.b[toY][toX] = board.b[chooseY][chooseX];
											board.b[chooseY][chooseX] = -1;

										}
										else {
											cout << "輸入的座標不可達，請重新輸入:";
											again = true;
										}
										break;
									}
								}
							}
							if (again) continue;
							break;
						}
					}
				}
			}
		}
		viewer.update(board);
		viewer.print(board);
		if (ff != -1) {
			if (ff == 1) {
				std::cout << "黑方投降，紅方獲勝\n";
			}
			else {
				std::cout << "紅方投降，黑方獲勝\n";
			}
			break;
		}
		else if (judge()) {
			break;
		}
		else {
			current_player = !current_player;
		}
	}
}

bool GameManager::judge() {
	// 檢查是否結束遊戲
	/*
	for (int i = 0; i < 10; i++) {
		for (int j = 0; j < 9; j++) {
			std::cout << this->board.b[i][j] << " ";
		}
		std::cout << "\n";
	}
	*/
	bool redGeneral = false;
	bool blackGeneral = false;
	for (int i = 0; i < 10; i++) {
		for (int j = 0; j < 9; j++) {
			if (this->board.b[i][j] == 7) {
				//std::cout << "找到帥\n";
				redGeneral = true;
			}
			if (this->board.b[i][j] == 0) {
				//std::cout << "找到將\n";
				blackGeneral = true;
			}
		}
	}
	if (redGeneral && blackGeneral) {
		//std::cout << "4\n";
	}
	else if (redGeneral) {
		std::cout << "將死亡，黑方獲勝\n";
		return true;
	}
	else if (blackGeneral) {
		std::cout << "帥死亡，紅方獲勝\n";
		return true;
	}

	// 檢查是否將軍，甚至是將死
	if (check(true, this->board)) {
		std::cout << "將軍!，請保護你的帥\n";
		if (generalDied(true)) {
			std::cout << "黑方將死，恭喜紅方獲勝\n";
			return true;
		}
	}
	else if (check(false, this->board)) {
		std::cout << "將軍!，請保護你的將\n";
		if (generalDied(false)) {
			std::cout << "紅方將死，恭喜黑方獲勝\n";
			return true;
		}
	}
	else {  // 沒將軍看是否欠行
		if (stalemate(true, this->board)) {
			std::cout << "黑方欠行，恭喜紅方獲勝\n";
			return true;
		}
		if (stalemate(false, this->board)) {
			std::cout << "紅方欠行，恭喜黑方獲勝\n";
			return true;
		}
	}


	return false;
}

bool GameManager::checkPlayer(int x, int y) {
	for (int i = 0; i < on_board.size(); i++) {
		Position tmp = on_board[i]->getPosition();
		if (tmp.x == x && tmp.y == y) {
			return (current_player != this->on_board[i]->type);
		}
	}
}

Chess* GameManager::find(int x, int y) {
	for (int i = 0; i < on_board.size(); i++) {
		Position tmp = on_board[i]->getPosition();
		if (tmp.x == x && tmp.y == y) {
			return on_board[i];
		}
	}
}

bool GameManager::check(bool player, Board B) {
	std::vector<Chess*> enemy;
	enemy.clear();
	Position gPosition;	 // General position
	//Position egPosition; // Enemy General position
	//std::cout << "check\n";
	// 找出enemy
	int low;
	int high;
	int generalID;
	if (player) {  // true 0 ~ 6
		low = 0;
		high = 6;
		generalID = 7;
	}
	else {		   // false 7 ~ 13
		low = 7;
		high = 13;
		generalID = 0;
	}
	//進入盤面找
	Chess* tmp;
	for (int i = 0; i < 10; i++) {
		for (int j = 0; j < 9; j++) {
			if (B.b[i][j] >= low && B.b[i][j] <= high) {
				switch (B.b[i][j] % 7) {
				case 0: {
					tmp = new General(Position{ i, j }, !player);
					enemy.push_back(tmp);
					break;
				}
				case 1: {
					tmp = new Advisor(Position{ i, j }, !player);
					enemy.push_back(tmp);
					break;
				}
				case 2: {
					tmp = new Elephant(Position{ i, j }, !player);
					enemy.push_back(tmp);
					break;
				}
				case 3: {
					tmp = new Horse(Position{ i, j }, !player);
					enemy.push_back(tmp);
					break;
				}
				case 4: {
					tmp = new Chariot(Position{ i, j }, !player);
					enemy.push_back(tmp);
					break;
				}
				case 5: {
					tmp = new Cannon(Position{ i, j }, !player);
					enemy.push_back(tmp);
					break;
				}
				case 6: {
					tmp = new Soldier(Position{ i, j }, !player);
					enemy.push_back(tmp);
					break;
				}
				default:
					break;
				}
			}
			if (board.b[i][j] == generalID) {
				gPosition.x = j;
				gPosition.y = i;
			}
		}
	}

	// 是否有棋子可以走過去吃掉將軍
	//std::cout << "General ID: " << generalID << "\n";
	//std::cout << "General Position: " << gPosition.x << " " << gPosition.y << "\n";
	//std::cout << "Enemy:\n";
	//std::cout << "\n";
	for (int i = 0; i < enemy.size(); i++) {
		//std::cout << enemy[i]->id << ": " << enemy[i]->p.x << " " << enemy[i]->p.y << "\n";
		if (enemy[i]->move(B, gPosition)) {
			//std::cout << enemy[i]->p.x << " " << enemy[i]->p.y << "   "  << enemy[i]->id << "\n";
			return true;
		}
	}

	return false;
}

bool GameManager::generalDied(bool player) {

	// 找友軍
	Board temp;				// 儲存暫時版面
	std::vector<Chess*> me;	// 友軍
	me.clear();
	//Position gPosition;		// General position
	//Position egPosition;	// Enemy General position

	// 找出友軍
	int low;
	int high;
	if (player) {  // true 7 ~ 13
		low = 7;
		high = 13;
	}
	else {		   // false 0 ~ 6
		low = 0;
		high = 6;
	}
	// 進入盤面找
	Chess* tmp;
	for (int i = 0; i < 10; i++) {
		for (int j = 0; j < 9; j++) {
			if (board.b[i][j] >= low && board.b[i][j] <= high) {
				switch (board.b[i][j] % 7) {
				case 0: {
					tmp = new General(Position{ i, j }, player);
					me.push_back(tmp);
					break;
				}
				case 1: {
					tmp = new Advisor(Position{ i, j }, player);
					me.push_back(tmp);
					break;
				}
				case 2: {
					tmp = new Elephant(Position{ i, j }, player);
					me.push_back(tmp);
					break;
				}
				case 3: {
					tmp = new Horse(Position{ i, j }, player);
					me.push_back(tmp);
					break;
				}
				case 4: {
					tmp = new Chariot(Position{ i, j }, player);
					me.push_back(tmp);
					break;
				}
				case 5: {
					tmp = new Cannon(Position{ i, j }, player);
					me.push_back(tmp);
					break;
				}
				case 6: {
					tmp = new Soldier(Position{ i, j }, player);
					me.push_back(tmp);
					break;
				}
				default:
					break;
				}
			}
		}
	}

	//檢查將死
	for (int it = 0; it < me.size(); it++) {
		for (int i = 0; i < 10; i++) {
			for (int j = 0; j < 9; j++) {
				temp = this->board;

				//看棋盤每一個地方可不可以走，可以就走過去
				if (me[it]->move(this->board, Position{i, j})) {
					temp.b[i][j] = me[it]->id;
					temp.b[me[it]->p.y][me[it]->p.x] = -1;

					//走過去不是仍為將軍，或沒有王見王，則確定沒有將死，return false
					if (!check(player, temp) && !faceToFace(temp)) {
						return false;
					}
				}
			}
		}
	}

	return true;

	//return false;
}

bool GameManager::faceToFace(Board B) {
	Position g;
	Position eg;
	for (int i = 0; i < 10; i++) {
		for (int j = 0; j < 9; j++) {
			if (B.b[i][j] == 0) {
				g.x = j;
				g.y = i;
			}
			else if (B.b[i][j] == 7) {
				eg.x = j;
				eg.y = i;
			}
		}
	}
	//std::cout << "check face to face: \n";
	//std::cout << g.x << " " << g.y << "\n";
	//std::cout << eg.x << " " << eg.y << "\n";

	int yStart = g.y;
	int yEnd = eg.y;
	if (g.x != eg.x) {
		return false;
	}
	else {
		//std::cout << "5: \n";
		if (yStart > yEnd) {
			swap(yStart, yEnd);
		}
		for (int i = yStart + 1; i < yEnd; i++) {
			//std::cout << B.b[i][g.x] << " ";
			if (B.b[i][g.x] != -1) {
				return false;
			}
		}
		//std::cout << "\n";
		return true;
	}
}

bool GameManager::stalemate(bool player, Board B) {
	Board temp;				// 儲存暫時版面
	std::vector<Chess*> me;	// 友軍
	//Position gPosition;		// General position
	//Position egPosition;	// Enemy General position

	// 找出友軍
	int low;
	int high;
	if (player) {  // true 7 ~ 13
		low = 7;
		high = 13;
	}
	else {		   // false 0 ~ 6
		low = 0;
		high = 6;
	}
	// 進入盤面找
	Chess* tmp;
	for (int i = 0; i < 10; i++) {
		for (int j = 0; j < 9; j++) {
			if (board.b[i][j] >= low && board.b[i][j] <= high) {
				switch (board.b[i][j] % 7) {
				case 0: {
					tmp = new General(Position{ i, j }, player);
					me.push_back(tmp);
					break;
				}
				case 1: {
					tmp = new Advisor(Position{ i, j }, player);
					me.push_back(tmp);
					break;
				}
				case 2: {
					tmp = new Elephant(Position{ i, j }, player);
					me.push_back(tmp);
					break;
				}
				case 3: {
					tmp = new Horse(Position{ i, j }, player);
					me.push_back(tmp);
					break;
				}
				case 4: {
					tmp = new Chariot(Position{ i, j }, player);
					me.push_back(tmp);
					break;
				}
				case 5: {
					tmp = new Cannon(Position{ i, j }, player);
					me.push_back(tmp);
					break;
				}
				case 6: {
					tmp = new Soldier(Position{ i, j }, player);
					me.push_back(tmp);
					break;
				}
				default:
					break;
				}
			}
		}
	}

	//
	for (int it = 0; it < me.size(); it++) {
		for (int i = 0; i < 10; i++) {
			for (int j = 0; j < 9; j++) {
				Position next{ i, j };
				if (me[it]->id != 0 && me[it]->id != 7) {
					if (me[it]->move(B, next)) {
						return false;
					}
				}
				else {
					if (me[it]->move(B, next)) {
						Board t = B;
						t.b[next.y][next.x] = me[it]->id;
						t.b[me[it]->p.y][me[it]->p.y] = -1;
						if (!faceToFace(t)) {
							return false;
						}
					}
				}
			}
		}
	}
}


class FileGameManager {
public:
	fstream f;
	std::vector<Chess*> on_board;
	bool current_player;
	Board board;
	Viewer viewer;
	int ff = -1;  // -1 沒投降，0 將投降， 1 帥投降
public:
	FileGameManager();
	void initialize();
	void play();
	bool checkPlayer(int x, int y);
	Chess* find(int x, int y);
	bool judge();
	bool check(bool player, Board B);					//將軍
	bool generalDied(bool player);						//將死
	bool stalemate(bool player, Board B);				//欠行
	bool faceToFace(Board B);	//王見王
};


FileGameManager::FileGameManager() {
	current_player = 0;
	//memset(board.b, ' ', 90);
}

void FileGameManager::initialize() {
	on_board.clear();
	board.restart();
	viewer.viewerClear();
	Chess* r1 = new General({ 0, 4 }, 0), * b1 = new General({ 9, 4 }, 1);
	Chess* r2 = new Advisor({ 0, 3 }, 0), * r3 = new Advisor({ 0, 5 }, 0);
	Chess* b2 = new Advisor({ 9, 3 }, 1), * b3 = new Advisor({ 9, 5 }, 1);
	//cout << r2.getID() << "\n";
	on_board.push_back(r1);
	on_board.push_back(b1);
	on_board.push_back(r2);
	on_board.push_back(r3);
	on_board.push_back(b2);
	on_board.push_back(b3);
	Chess* r4 = new Elephant({ 0, 2 }, 0);
	Chess* r5 = new Elephant({ 0, 6 }, 0);
	Chess* b4 = new Elephant({ 9, 2 }, 1);
	Chess* b5 = new Elephant({ 9, 6 }, 1);
	on_board.push_back(r4);
	on_board.push_back(r5);
	on_board.push_back(b4);
	on_board.push_back(b5);
	Chess* r6 = new Horse({ 0, 1 }, 0);
	Chess* r7 = new Horse({ 0, 7 }, 0);
	Chess* b6 = new Horse({ 9, 1 }, 1);
	Chess* b7 = new Horse({ 9, 7 }, 1);
	on_board.push_back(r6);
	on_board.push_back(r7);
	on_board.push_back(b6);
	on_board.push_back(b7);
	Chess* r8 = new Chariot({ 0, 0 }, 0);
	Chess* r9 = new Chariot({ 0, 8 }, 0);
	Chess* b8 = new Chariot({ 9, 0 }, 1);
	Chess* b9 = new Chariot({ 9, 8 }, 1);
	on_board.push_back(r8);
	on_board.push_back(r9);
	on_board.push_back(b8);
	on_board.push_back(b9);
	Chess* r10 = new Cannon({ 2, 1 }, 0);
	Chess* r11 = new Cannon({ 2, 7 }, 0);
	Chess* b10 = new Cannon({ 7, 1 }, 1);
	Chess* b11 = new Cannon({ 7, 7 }, 1);
	on_board.push_back(r10);
	on_board.push_back(r11);
	on_board.push_back(b10);
	on_board.push_back(b11);
	Chess* r12 = new Soldier({ 3, 0 }, 0);
	Chess* r13 = new Soldier({ 3, 2 }, 0);
	Chess* r14 = new Soldier({ 3, 4 }, 0);
	Chess* r15 = new Soldier({ 3, 6 }, 0);
	Chess* r16 = new Soldier({ 3, 8 }, 0);
	Chess* b12 = new Soldier({ 6, 0 }, 1);
	Chess* b13 = new Soldier({ 6, 2 }, 1);
	Chess* b14 = new Soldier({ 6, 4 }, 1);
	Chess* b15 = new Soldier({ 6, 6 }, 1);
	Chess* b16 = new Soldier({ 6, 8 }, 1);
	on_board.push_back(r12);
	on_board.push_back(r13);
	on_board.push_back(r14);
	on_board.push_back(r15);
	on_board.push_back(r16);
	on_board.push_back(b12);
	on_board.push_back(b13);
	on_board.push_back(b14);
	on_board.push_back(b15);
	on_board.push_back(b16);
	for (int i = 0; i < on_board.size(); i++) {
		board.b[on_board[i]->p.y][on_board[i]->p.x] = on_board[i]->id;
		//cout << on_board[i]->p.y << " " << on_board[i]->p.x << "\n";
	}
	viewer.update(board);
}
//Player: 1, Action : Soldier (6, 6) -> (6, 5)
void FileGameManager::play() {
	initialize();
	viewer.update(board);
	viewer.print(board);
	f.open("test.txt", ios::in);
	string getStr1, getStr2, getStr3, getStr5;
	char getChar1, getChar2, getChar3, getChar4, getChar5, getChar6, getChar7, getCharaa;
	while (true) {
		int playerCheck = 0;
		int chooseX = 0, chooseY = 0, toX = 0, toY = 0;
		f >> getStr1 >> playerCheck >> getChar1 >> getStr2 >> getStr3 >> getCharaa
			>> chooseX >> getChar3 >> chooseY >> getChar4 >> getStr5
			>> getChar5 >> toX >> getChar6 >> toY >> getChar7;
		if (f.eof()) {
			break;
		}
		Chess* tmp = find(chooseX, chooseY);
		if (!(tmp->move(board, Position{ toY, toX }))) {
			cout << "輸入的座標不可達，請重新輸入: ";
		}
		else {
			Board t = this->board;
			if (tmp->id == 0 || tmp->id == 7) {
				t.b[toY][toX] = t.b[chooseY][chooseX];
				t.b[chooseY][chooseX] = -1;
			}
			if (board.b[toY][toX] == -1) {
				board.b[toY][toX] = board.b[chooseY][chooseX];
				board.b[chooseY][chooseX] = -1;
				tmp->setPosition(toX, toY);
			}
			else {
				for (int it = 0; it != on_board.size(); it++) {
					if (on_board[it]->getPosition().x == toX && on_board[it]->getPosition().y == toY) {
						if (on_board[it]->type != tmp->type) {
							tmp->p.x = toX;
							tmp->p.y = toY;
							on_board.erase(on_board.begin() + it);
							board.b[toY][toX] = board.b[chooseY][chooseX];
							board.b[chooseY][chooseX] = -1;

						}
						break;
					}
				}
			}
		}
		viewer.update(board);
		viewer.print(board);
		cout << getStr1 << " " << playerCheck << " " << getChar1 << " " << getStr2 << " " << getStr3 << " " << getCharaa
			<< " " << chooseX << " " << getChar3 << " " << chooseY << " " << getChar4 << " " << getStr5
			<< " " << getChar5 << " " << toX << " " << getChar6 << " " << toY << " " << getChar7 << "\n";
		if (judge()) {
			break;
		}
		else {
			current_player = !current_player;
		}
		system("pause");
		if (f.eof()) {
			break;
		}
	}
	system("pause");
	f.close();
	current_player = !current_player;
	while (true) {
		std::string input;
		int chooseX, chooseY;
		cout << "player" << current_player;
		cout << "，請輸入欲移動的棋子座標(輸入15ff投降): ";
		while (cin >> input) {
			if (input == "15ff") {
				if (current_player) {
					std::cout << "1\n";
					ff = 1;
					for (int i = 0; i < 10; i++) {
						for (int j = 0; j < 9; j++) {
							if (this->board.b[i][j] == 7) {
								this->board.b[i][j] = -1;
							}
						}
					}
				}
				else {
					std::cout << "2\n";
					ff = 0;
					for (int i = 0; i < 10; i++) {
						for (int j = 0; j < 9; j++) {
							if (this->board.b[i][j] == 0) {
								this->board.b[i][j] = -1;
							}
						}
					}
				}
				break;
			}
			else {
				cin >> chooseY;
				chooseX = stoi(input);
				if (chooseX < 9 && chooseX > -1 && chooseY < 10 && chooseY > -1) {
					if (board.b[chooseY][chooseX] == -1) {
						cout << "此位置無棋子，請重新輸入: ";
					}
					else if (checkPlayer(chooseX, chooseY)) {
						cout << "非你的棋子，請重新輸入: ";
					}
					else {
						break;
					}
				}
				else {
					cout << "已超出棋盤範圍，起重新輸入: ";
				}
			}
		}
		if (ff == -1) {
			Chess* tmp = find(chooseX, chooseY);
			/*
			vector<Position> step;
			step.clear();
			for (int i = 0; i < 10; i++) {
				for (int j = 0; j < 9; j++) {
					if ((tmp->move(board, Position{ i, j }))) {
						if (tmp->id == 0 || tmp->id == 7) {
							Board t = this->board;
							t.b[i][j] = t.b[chooseY][chooseX];
							t.b[chooseY][chooseX] = -1;
							if (!faceToFace(t)) {
								step.push_back(Position{ i, j });
								std::cout << "can move :" << j << " " << i << "\n";
							}
						}
						else
						{
							step.push_back(Position{ i, j });
							std::cout << "can move :" << j << " " << i << "\n";
						}
					}
				}
			}
			*/
			vector<Position> step = tmp->canGo();
			for (int i = 1; i < step.size(); i++) {
				if (!(tmp->move(board, step[i]))) {
					step.erase(step.begin() + i);
					i--;
				}
				Board t = this->board;
				if (tmp->id == 0 || tmp->id == 7) {
					t.b[step[i].y][step[i].x] = t.b[chooseY][chooseX];
					t.b[chooseY][chooseX] = -1;
					if (faceToFace(t)) {
						step.erase(step.begin() + i);
						i--;
					}
				}
			}

			viewer.printPath(board, step);
			/*
			for (auto output : step) {
				std::cout << "output:　" << output.x << " " << output.y << "\n";
			}
			*/
			/*
			if (step.size() == 0) {
				current_player = !current_player;
				std::cout << "此棋子無步可走，請重新選擇: ";
				continue;
			}
			*/
			int toX, toY;
			cout << "player" << current_player;
			cout << "，請輸入欲移動到的座標(輸入-1返回選擇棋子): ";
			while (cin >> toX) {
				if (toX == -1) {
					current_player = !current_player;
					break;
				}
				else {
					cin >> toY;
					bool again = false;
					if (!(tmp->move(board, Position{ toY, toX }))) {
						cout << "輸入的座標不可達，請重新輸入: ";
					}
					else {
						Board t = this->board;
						if (tmp->id == 0 || tmp->id == 7) {
							t.b[toY][toX] = t.b[chooseY][chooseX];
							t.b[chooseY][chooseX] = -1;
						}
						if (faceToFace(t)) {
							cout << "輸入的座標不可達，請重新輸入: ";
							again = true;
						}
						else {
							if (board.b[toY][toX] == -1) {
								board.b[toY][toX] = board.b[chooseY][chooseX];
								board.b[chooseY][chooseX] = -1;
								tmp->setPosition(toX, toY);
							}
							else {
								for (int it = 0; it != on_board.size(); it++) {
									if (on_board[it]->getPosition().x == toX && on_board[it]->getPosition().y == toY) {
										if (on_board[it]->type != tmp->type) {
											tmp->p.x = toX;
											tmp->p.y = toY;
											on_board.erase(on_board.begin() + it);
											board.b[toY][toX] = board.b[chooseY][chooseX];
											board.b[chooseY][chooseX] = -1;

										}
										else {
											cout << "輸入的座標不可達，請重新輸入:";
											again = true;
										}
										break;
									}
								}
							}
							if (again) continue;
							break;
						}
					}
				}
			}
		}
		viewer.update(board);
		viewer.print(board);
		if (ff != -1) {
			if (ff == 1) {
				std::cout << "黑方投降，紅方獲勝\n";
			}
			else {
				std::cout << "紅方投降，黑方獲勝\n";
			}
			break;
		}
		else if (judge()) {
			break;
		}
		else {
			current_player = !current_player;
		}
	}
}

bool FileGameManager::judge() {
	// 檢查是否結束遊戲
	/*
	for (int i = 0; i < 10; i++) {
		for (int j = 0; j < 9; j++) {
			std::cout << this->board.b[i][j] << " ";
		}
		std::cout << "\n";
	}
	*/
	bool redGeneral = false;
	bool blackGeneral = false;
	for (int i = 0; i < 10; i++) {
		for (int j = 0; j < 9; j++) {
			if (this->board.b[i][j] == 7) {
				//std::cout << "找到帥\n";
				redGeneral = true;
			}
			if (this->board.b[i][j] == 0) {
				//std::cout << "找到將\n";
				blackGeneral = true;
			}
		}
	}
	if (redGeneral && blackGeneral) {
		//std::cout << "4\n";
	}
	else if (redGeneral) {
		std::cout << "將死亡，黑方獲勝\n";
		return true;
	}
	else if (blackGeneral) {
		std::cout << "帥死亡，紅方獲勝\n";
		return true;
	}

	// 檢查是否將軍，甚至是將死
	if (check(true, this->board)) {
		std::cout << "將軍!，請保護你的帥\n";
		if (generalDied(true)) {
			std::cout << "黑方將死，恭喜紅方獲勝\n";
			return true;
		}
	}
	else if (check(false, this->board)) {
		std::cout << "將軍!，請保護你的將\n";
		if (generalDied(false)) {
			std::cout << "紅方將死，恭喜黑方獲勝\n";
			return true;
		}
	}
	else {  // 沒將軍看是否欠行
		if (stalemate(true, this->board)) {
			std::cout << "黑方欠行，恭喜紅方獲勝\n";
			return true;
		}
		if (stalemate(false, this->board)) {
			std::cout << "紅方欠行，恭喜黑方獲勝\n";
			return true;
		}
	}


	return false;
}

bool FileGameManager::checkPlayer(int x, int y) {
	for (int i = 0; i < on_board.size(); i++) {
		Position tmp = on_board[i]->getPosition();
		if (tmp.x == x && tmp.y == y) {
			return (current_player != this->on_board[i]->type);
		}
	}
}

Chess* FileGameManager::find(int x, int y) {
	for (int i = 0; i < on_board.size(); i++) {
		Position tmp = on_board[i]->getPosition();
		if (tmp.x == x && tmp.y == y) {
			return on_board[i];
		}
	}
}

bool FileGameManager::check(bool player, Board B) {
	std::vector<Chess*> enemy;
	enemy.clear();
	Position gPosition;	 // General position
	//Position egPosition; // Enemy General position
	//std::cout << "check\n";
	// 找出enemy
	int low;
	int high;
	int generalID;
	if (player) {  // true 0 ~ 6
		low = 0;
		high = 6;
		generalID = 7;
	}
	else {		   // false 7 ~ 13
		low = 7;
		high = 13;
		generalID = 0;
	}
	//進入盤面找
	Chess* tmp;
	for (int i = 0; i < 10; i++) {
		for (int j = 0; j < 9; j++) {
			if (B.b[i][j] >= low && B.b[i][j] <= high) {
				switch (B.b[i][j] % 7) {
				case 0: {
					tmp = new General(Position{ i, j }, !player);
					enemy.push_back(tmp);
					break;
				}
				case 1: {
					tmp = new Advisor(Position{ i, j }, !player);
					enemy.push_back(tmp);
					break;
				}
				case 2: {
					tmp = new Elephant(Position{ i, j }, !player);
					enemy.push_back(tmp);
					break;
				}
				case 3: {
					tmp = new Horse(Position{ i, j }, !player);
					enemy.push_back(tmp);
					break;
				}
				case 4: {
					tmp = new Chariot(Position{ i, j }, !player);
					enemy.push_back(tmp);
					break;
				}
				case 5: {
					tmp = new Cannon(Position{ i, j }, !player);
					enemy.push_back(tmp);
					break;
				}
				case 6: {
					tmp = new Soldier(Position{ i, j }, !player);
					enemy.push_back(tmp);
					break;
				}
				default:
					break;
				}
			}
			if (board.b[i][j] == generalID) {
				gPosition.x = j;
				gPosition.y = i;
			}
		}
	}

	// 是否有棋子可以走過去吃掉將軍
	//std::cout << "General ID: " << generalID << "\n";
	//std::cout << "General Position: " << gPosition.x << " " << gPosition.y << "\n";
	//std::cout << "Enemy:\n";
	//std::cout << "\n";
	for (int i = 0; i < enemy.size(); i++) {
		//std::cout << enemy[i]->id << ": " << enemy[i]->p.x << " " << enemy[i]->p.y << "\n";
		if (enemy[i]->move(B, gPosition)) {
			//std::cout << enemy[i]->p.x << " " << enemy[i]->p.y << "   "  << enemy[i]->id << "\n";

			return true;
		}
	}

	return false;
}

bool FileGameManager::generalDied(bool player) {

	// 找友軍
	Board temp;				// 儲存暫時版面
	std::vector<Chess*> me;	// 友軍
	me.clear();
	//Position gPosition;		// General position
	//Position egPosition;	// Enemy General position

	// 找出友軍
	int low;
	int high;
	if (player) {  // true 7 ~ 13
		low = 7;
		high = 13;
	}
	else {		   // false 0 ~ 6
		low = 0;
		high = 6;
	}
	// 進入盤面找
	Chess* tmp;
	for (int i = 0; i < 10; i++) {
		for (int j = 0; j < 9; j++) {
			if (board.b[i][j] >= low && board.b[i][j] <= high) {
				switch (board.b[i][j] % 7) {
				case 0: {
					tmp = new General(Position{ i, j }, player);
					me.push_back(tmp);
					break;
				}
				case 1: {
					tmp = new Advisor(Position{ i, j }, player);
					me.push_back(tmp);
					break;
				}
				case 2: {
					tmp = new Elephant(Position{ i, j }, player);
					me.push_back(tmp);
					break;
				}
				case 3: {
					tmp = new Horse(Position{ i, j }, player);
					me.push_back(tmp);
					break;
				}
				case 4: {
					tmp = new Chariot(Position{ i, j }, player);
					me.push_back(tmp);
					break;
				}
				case 5: {
					tmp = new Cannon(Position{ i, j }, player);
					me.push_back(tmp);
					break;
				}
				case 6: {
					tmp = new Soldier(Position{ i, j }, player);
					me.push_back(tmp);
					break;
				}
				default:
					break;
				}
			}
		}
	}

	//檢查將死
	for (int it = 0; it < me.size(); it++) {
		for (int i = 0; i < 10; i++) {
			for (int j = 0; j < 9; j++) {
				temp = this->board;

				//看棋盤每一個地方可不可以走，可以就走過去
				if (me[it]->move(this->board, Position{i, j})) {
					temp.b[i][j] = me[it]->id;
					temp.b[me[it]->p.y][me[it]->p.x] = -1;

					//走過去不是仍為將軍，或沒有王見王，則確定沒有將死，return false
					if (!check(player, temp) && !faceToFace(temp)) {
						return false;
					}
				}
			}
		}
	}

	return true;

	//return false;
}

bool FileGameManager::faceToFace(Board B) {
	Position g;
	Position eg;
	for (int i = 0; i < 10; i++) {
		for (int j = 0; j < 9; j++) {
			if (B.b[i][j] == 0) {
				g.x = j;
				g.y = i;
			}
			else if (B.b[i][j] == 7) {
				eg.x = j;
				eg.y = i;
			}
		}
	}
	//std::cout << "check face to face: \n";
	//std::cout << g.x << " " << g.y << "\n";
	//std::cout << eg.x << " " << eg.y << "\n";

	int yStart = g.y;
	int yEnd = eg.y;
	if (g.x != eg.x) {
		return false;
	}
	else {
		//std::cout << "5: \n";
		if (yStart > yEnd) {
			swap(yStart, yEnd);
		}
		for (int i = yStart + 1; i < yEnd; i++) {
			//std::cout << B.b[i][g.x] << " ";
			if (B.b[i][g.x] != -1) {
				return false;
			}
		}
		//std::cout << "\n";
		return true;
	}
}

bool FileGameManager::stalemate(bool player, Board B) {
	Board temp;				// 儲存暫時版面
	std::vector<Chess*> me;	// 友軍
	//Position gPosition;		// General position
	//Position egPosition;	// Enemy General position

	// 找出友軍
	int low;
	int high;
	if (player) {  // true 7 ~ 13
		low = 7;
		high = 13;
	}
	else {		   // false 0 ~ 6
		low = 0;
		high = 6;
	}
	// 進入盤面找
	Chess* tmp;
	for (int i = 0; i < 10; i++) {
		for (int j = 0; j < 9; j++) {
			if (board.b[i][j] >= low && board.b[i][j] <= high) {
				switch (board.b[i][j] % 7) {
				case 0: {
					tmp = new General(Position{ i, j }, player);
					me.push_back(tmp);
					break;
				}
				case 1: {
					tmp = new Advisor(Position{ i, j }, player);
					me.push_back(tmp);
					break;
				}
				case 2: {
					tmp = new Elephant(Position{ i, j }, player);
					me.push_back(tmp);
					break;
				}
				case 3: {
					tmp = new Horse(Position{ i, j }, player);
					me.push_back(tmp);
					break;
				}
				case 4: {
					tmp = new Chariot(Position{ i, j }, player);
					me.push_back(tmp);
					break;
				}
				case 5: {
					tmp = new Cannon(Position{ i, j }, player);
					me.push_back(tmp);
					break;
				}
				case 6: {
					tmp = new Soldier(Position{ i, j }, player);
					me.push_back(tmp);
					break;
				}
				default:
					break;
				}
			}
		}
	}

	//
	for (int it = 0; it < me.size(); it++) {
		for (int i = 0; i < 10; i++) {
			for (int j = 0; j < 9; j++) {
				Position next{ i, j };
				if (me[it]->id != 0 && me[it]->id != 7) {
					if (me[it]->move(B, next)) {
						return false;
					}
				}
				else {
					if (me[it]->move(B, next)) {
						Board t = B;
						t.b[next.y][next.x] = me[it]->id;
						t.b[me[it]->p.y][me[it]->p.y] = -1;
						if (!faceToFace(t)) {
							return false;
						}
					}
				}
			}
		}
	}
}