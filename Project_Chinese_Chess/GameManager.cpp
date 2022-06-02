//#include "GameManager.h"
//
//GameManager::GameManager() {
//	current_player = 0;
//	//memset(board.b, ' ', 90);
//}
//
//void GameManager::initialize() {
//	ff = -1;
//	on_board.clear();
//	board.restart();
//	viewer.viewerClear();
//	Chess* r1 = new General({ 0, 4 }, 0), * b1 = new General({ 9, 4 }, 1);
//	Chess* r2 = new Advisor({ 0, 3 }, 0), * r3 = new Advisor({ 0, 5 }, 0);
//	Chess* b2 = new Advisor({ 9, 3 }, 1), * b3 = new Advisor({ 9, 5 }, 1);
//	//cout << r2.getID() << "\n";
//	on_board.push_back(r1);
//	on_board.push_back(b1);
//	on_board.push_back(r2);
//	on_board.push_back(r3);
//	on_board.push_back(b2);
//	on_board.push_back(b3);
//	Chess* r4 = new Elephant({ 0, 2 }, 0);
//	Chess* r5 = new Elephant({ 0, 6 }, 0);
//	Chess* b4 = new Elephant({ 9, 2 }, 1);
//	Chess* b5 = new Elephant({ 9, 6 }, 1);
//	on_board.push_back(r4);
//	on_board.push_back(r5);
//	on_board.push_back(b4);
//	on_board.push_back(b5);
//	Chess* r6 = new Horse({ 0, 1 }, 0);
//	Chess* r7 = new Horse({ 0, 7 }, 0);
//	Chess* b6 = new Horse({ 9, 1 }, 1);
//	Chess* b7 = new Horse({ 9, 7 }, 1);
//	on_board.push_back(r6);
//	on_board.push_back(r7);
//	on_board.push_back(b6);
//	on_board.push_back(b7);
//	Chess* r8 = new Chariot({ 0, 0 }, 0);
//	Chess* r9 = new Chariot({ 0, 8 }, 0);
//	Chess* b8 = new Chariot({ 9, 0 }, 1);
//	Chess* b9 = new Chariot({ 9, 8 }, 1);
//	on_board.push_back(r8);
//	on_board.push_back(r9);
//	on_board.push_back(b8);
//	on_board.push_back(b9);
//	Chess* r10 = new Cannon({ 2, 1 }, 0);
//	Chess* r11 = new Cannon({ 2, 7 }, 0);
//	Chess* b10 = new Cannon({ 7, 1 }, 1);
//	Chess* b11 = new Cannon({ 7, 7 }, 1);
//	on_board.push_back(r10);
//	on_board.push_back(r11);
//	on_board.push_back(b10);
//	on_board.push_back(b11);
//	Chess* r12 = new Soldier({ 3, 0 }, 0);
//	Chess* r13 = new Soldier({ 3, 2 }, 0);
//	Chess* r14 = new Soldier({ 3, 4 }, 0);
//	Chess* r15 = new Soldier({ 3, 6 }, 0);
//	Chess* r16 = new Soldier({ 3, 8 }, 0);
//	Chess* b12 = new Soldier({ 6, 0 }, 1);
//	Chess* b13 = new Soldier({ 6, 2 }, 1);
//	Chess* b14 = new Soldier({ 6, 4 }, 1);
//	Chess* b15 = new Soldier({ 6, 6 }, 1);
//	Chess* b16 = new Soldier({ 6, 8 }, 1);
//	on_board.push_back(r12);
//	on_board.push_back(r13);
//	on_board.push_back(r14);
//	on_board.push_back(r15);
//	on_board.push_back(r16);
//	on_board.push_back(b12);
//	on_board.push_back(b13);
//	on_board.push_back(b14);
//	on_board.push_back(b15);
//	on_board.push_back(b16);
//	for (int i = 0; i < on_board.size(); i++) {
//		board.b[on_board[i]->p.y][on_board[i]->p.x] = on_board[i]->id + (on_board[i]->type * 7);
//		//cout << on_board[i]->p.y << " " << on_board[i]->p.x << "\n";
//	}
//	viewer.update(board);
//}
//
//void GameManager::play() {
//	initialize();
//	viewer.update(board);
//	viewer.print(board);
//	while (true) {
//		std::string input;
//		int chooseX, chooseY;
//		cout << "player" << current_player;
//		cout << "�A�п�J�����ʪ��Ѥl�y��(��J15ff�뭰): ";
//		while (cin >> input) {
//			if (input == "15ff") {
//				if (current_player) {
//					std::cout << "1\n";
//					ff = 1;
//					for (int i = 0; i < 10; i++) {
//						for (int j = 0; j < 9; j++) {
//							if (this->board.b[i][j] == 7) {
//								this->board.b[i][j] = -1;
//							}
//						}
//					}
//				}
//				else {
//					std::cout << "2\n";
//					ff = 0;
//					for (int i = 0; i < 10; i++) {
//						for (int j = 0; j < 9; j++) {
//							if (this->board.b[i][j] == 0) {
//								this->board.b[i][j] = -1;
//							}
//						}
//					}
//				}
//				break;
//			}
//			else {
//				cin >> chooseY;
//				chooseX = stoi(input);
//				if (chooseX < 9 && chooseX > -1 && chooseY < 10 && chooseY > -1) {
//					if (board.b[chooseY][chooseX] == -1) {
//						cout << "����m�L�Ѥl�A�Э��s��J: ";
//					}
//					else if (checkPlayer(chooseX, chooseY)) {
//						cout << "�D�A���Ѥl�A�Э��s��J: ";
//					}
//					else {
//						break;
//					}
//				}
//				else {
//					cout << "�w�W�X�ѽL�d��A�_���s��J: ";
//				}
//			}
//		}
//		if (ff == -1) {
//			int toX, toY;
//			cout << "player" << current_player;
//			cout << "�A�п�J�����ʨ쪺�y��(��J-1��^��ܴѤl): ";
//			while (cin >> toX) {
//				if (toX == -1) {
//					current_player = !current_player;
//					break;
//				}
//				else {
//					cin >> toY;
//					bool again = false;
//					Chess* tmp = find(chooseX, chooseY);
//					if (!(tmp->move(board, Position{ toY, toX }))) {
//						cout << "��J���y�Ф��i�F�A�Э��s��J: ";
//					}
//					else {
//						Board t = this->board;
//						if (tmp->id == 0 || tmp->id == 7) {
//							t.b[toY][toX] = t.b[chooseY][chooseX];
//							t.b[chooseY][chooseX] = -1;
//						}
//						if (faceToFace(t)) {
//							cout << "��J���y�Ф��i�F�A�Э��s��J: ";
//							again = true;
//						}
//						else {
//							if (board.b[toY][toX] == -1) {
//								board.b[toY][toX] = board.b[chooseY][chooseX];
//								board.b[chooseY][chooseX] = -1;
//								tmp->setPosition(toX, toY);
//							}
//							else {
//								for (int it = 0; it != on_board.size(); it++) {
//									if (on_board[it]->getPosition().x == toX && on_board[it]->getPosition().y == toY) {
//										if (on_board[it]->type != tmp->type) {
//											tmp->p.x = toX;
//											tmp->p.y = toY;
//											on_board.erase(on_board.begin() + it);
//											board.b[toY][toX] = board.b[chooseY][chooseX];
//											board.b[chooseY][chooseX] = -1;
//
//										}
//										else {
//											cout << "��J���y�Ф��i�F�A�Э��s��J:";
//											again = true;
//										}
//										break;
//									}
//								}
//							}
//							if (again) continue;
//							break;
//						}
//					}
//				}
//			}
//		}
//		viewer.update(board);
//		viewer.print(board);
//		if (ff != -1) {
//			if (ff == 1) {
//				std::cout << "�¤�뭰�A�������\n";
//			}
//			else {
//				std::cout << "����뭰�A�¤����\n";
//			}
//			break;
//		}
//		else if (judge()) {
//			break;
//		}
//		else {
//			current_player = !current_player;
//		}
//	}
//}
//
//bool GameManager::judge() {
//	// �ˬd�O�_�����C��
//	/*
//	for (int i = 0; i < 10; i++) {
//		for (int j = 0; j < 9; j++) {
//			std::cout << this->board.b[i][j] << " ";
//		}
//		std::cout << "\n";
//	}
//	*/
//	bool redGeneral = false;
//	bool blackGeneral = false;
//	for (int i = 0; i < 10; i++) {
//		for (int j = 0; j < 9; j++) {
//			if (this->board.b[i][j] == 7) {
//				//std::cout << "����\n";
//				redGeneral = true;
//			}
//			if (this->board.b[i][j] == 0) {
//				//std::cout << "���N\n";
//				blackGeneral = true;
//			}
//		}
//	}
//	if (redGeneral && blackGeneral) {
//		//std::cout << "4\n";
//	}
//	else if (redGeneral) {
//		std::cout << "�N���`�A�������\n";
//		return true;
//	}
//	else if (blackGeneral) {
//		std::cout << "�Ӧ��`�A�¤����\n";
//		return true;
//	}
//
//	// �ˬd�O�_�N�x�A�ƦܬO�N��
//	if (check(true, this->board)) {
//		std::cout << "�N�x!�A�ЫO�@�A����\n";
//		if (generalDied(true)) {
//			std::cout << "����N���A���߶¤����\n";
//			return true;
//		}
//	}
//	else if (check(false, this->board)) {
//		std::cout << "�N�x!�A�ЫO�@�A���N\n";
//		if (generalDied(false)) {
//			std::cout << "����N���A���߶¤����\n";
//			return true;
//		}
//	}
//	else {  // �S�N�x�ݬO�_���
//		if (stalemate(true, this->board)) {
//			std::cout << "������A���߶¤����\n";
//			return true;
//		}
//		if (stalemate(false, this->board)) {
//			std::cout << "�¤���A���߬������\n";
//			return true;
//		}
//	}
//
//
//	return false;
//}
//
//bool GameManager::checkPlayer(int x, int y) {
//	for (int i = 0; i < on_board.size(); i++) {
//		Position tmp = on_board[i]->getPosition();
//		if (tmp.x == x && tmp.y == y) {
//			return (current_player != this->on_board[i]->type);
//		}
//	}
//}
//
//Chess* GameManager::find(int x, int y) {
//	for (int i = 0; i < on_board.size(); i++) {
//		Position tmp = on_board[i]->getPosition();
//		if (tmp.x == x && tmp.y == y) {
//			return on_board[i];
//		}
//	}
//}
//
//bool GameManager::check(bool player, Board B) {
//	std::vector<Chess*> enemy;
//	Position gPosition;	 // General position
//	//Position egPosition; // Enemy General position
//
//	// ��Xenemy
//	int low;
//	int high;
//	int generalID;
//	if (player) {  // true 0 ~ 6
//		low = 0;
//		high = 6;
//		generalID = 7;
//	}
//	else {		   // false 7 ~ 13
//		low = 7;
//		high = 13;
//		generalID = 0;
//	}
//	//�i�J�L����
//	Chess* tmp;
//	for (int i = 0; i < 10; i++) {
//		for (int j = 0; j < 9; j++) {
//			if (B.b[i][j] >= low && B.b[i][j] <= high) {
//				switch (B.b[i][j] % 7) {
//				case 0: {
//					tmp = new General(Position{ i, j }, !player);
//					enemy.push_back(tmp);
//					break;
//				}
//				case 1: {
//					tmp = new Advisor(Position{ i, j }, !player);
//					enemy.push_back(tmp);
//					break;
//				}
//				case 2: {
//					tmp = new Elephant(Position{ i, j }, !player);
//					enemy.push_back(tmp);
//					break;
//				}
//				case 3: {
//					tmp = new Horse(Position{ i, j }, !player);
//					enemy.push_back(tmp);
//					break;
//				}
//				case 4: {
//					tmp = new Chariot(Position{ j, i }, !player);
//					enemy.push_back(tmp);
//					break;
//				}
//				case 5: {
//					tmp = new Cannon(Position{ i, j }, !player);
//					enemy.push_back(tmp);
//					break;
//				}
//				case 6: {
//					tmp = new Soldier(Position{ i, j }, !player);
//					enemy.push_back(tmp);
//					break;
//				}
//				default:
//					break;
//				}
//			}
//			if (board.b[i][j] == generalID) {
//				gPosition.x = j;
//				gPosition.y = i;
//			}
//		}
//	}
//
//	// �O�_���Ѥl�i�H���L�h�Y���N�x
//	//std::cout << "General ID: " << generalID << "\n";
//	//std::cout << "General Position: " << gPosition.x << " " << gPosition.y << "\n";
//	//std::cout << "Enemy:\n";
//	for (int i = 0; i < enemy.size(); i++) {
//		//std::cout << enemy[i]->id << ": " << enemy[i]->p.x << " " << enemy[i]->p.y << "\n";
//		Chess* temp = enemy[i];
//		if (temp->move(B, gPosition)) {
//			return true;
//		}
//	}
//
//	return false;
//}
//
//bool GameManager::generalDied(bool player) {
//
//	// ��ͭx
//	Board temp;				// �x�s�Ȯɪ���
//	std::vector<Chess*> me;	// �ͭx
//	//Position gPosition;		// General position
//	//Position egPosition;	// Enemy General position
//
//	// ��X�ͭx
//	int low;
//	int high;
//	if (player) {  // true 7 ~ 13
//		low = 7;
//		high = 13;
//	}
//	else {		   // false 0 ~ 6
//		low = 0;
//		high = 6;
//	}
//	// �i�J�L����
//	Chess* tmp;
//	for (int i = 0; i < 10; i++) {
//		for (int j = 0; j < 9; j++) {
//			if (board.b[i][j] >= low && board.b[i][j] <= high) {
//				switch (board.b[i][j] % 7) {
//				case 0: {
//					tmp = new General(Position{ i, j }, player);
//					me.push_back(tmp);
//					break;
//				}
//				case 1: {
//					tmp = new Advisor(Position{ i, j }, player);
//					me.push_back(tmp);
//					break;
//				}
//				case 2: {
//					tmp = new Elephant(Position{ i, j }, player);
//					me.push_back(tmp);
//					break;
//				}
//				case 3: {
//					tmp = new Horse(Position{ i, j }, player);
//					me.push_back(tmp);
//					break;
//				}
//				case 4: {
//					tmp = new Chariot(Position{ i, j }, player);
//					me.push_back(tmp);
//					break;
//				}
//				case 5: {
//					tmp = new Cannon(Position{ i, j }, player);
//					me.push_back(tmp);
//					break;
//				}
//				case 6: {
//					tmp = new Soldier(Position{ i, j }, player);
//					me.push_back(tmp);
//					break;
//				}
//				default:
//					break;
//				}
//			}
//		}
//	}
//
//	//�ˬd�N��
//	for (int it = 0; it < me.size(); it++) {
//		for (int i = 0; i < 10; i++) {
//			for (int j = 0; j < 9; j++) {
//				temp = this->board;
//
//				//�ݴѽL�C�@�Ӧa��i���i�H���A�i�H�N���L�h
//				if (me[it]->move(this->board, Position{i, j})) {
//					temp.b[i][j] = me[it]->id;
//					temp.b[me[it]->p.y][me[it]->p.x] = -1;
//
//					//���L�h���O�����N�x�A�ΨS���������A�h�T�w�S���N���Areturn false
//					if (!check(player, temp) && !faceToFace(temp)) {
//						return false;
//					}
//				}
//			}
//		}
//	}
//
//	return true;
//
//	//return false;
//}
//
//bool GameManager::faceToFace(Board B) {
//	Position g;
//	Position eg;
//	for (int i = 0; i < 10; i++) {
//		for (int j = 0; j < 9; j++) {
//			if (B.b[i][j] == 0) {
//				g.x = j;
//				g.y = i;
//			}
//			else if (B.b[i][j] == 7) {
//				eg.x = j;
//				eg.y = i;
//			}
//		}
//	}
//	//std::cout << "check face to face: \n";
//	//std::cout << g.x << " " << g.y << "\n";
//	//std::cout << eg.x << " " << eg.y << "\n";
//
//	int yStart = g.y;
//	int yEnd = eg.y;
//	if (g.x != eg.x) {
//		return false;
//	}
//	else {
//		//std::cout << "5: \n";
//		if (yStart > yEnd) {
//			swap(yStart, yEnd);
//		}
//		for (int i = yStart + 1; i < yEnd; i++) {
//			//std::cout << B.b[i][g.x] << " ";
//			if (B.b[i][g.x] != -1) {
//				return false;
//			}
//		}
//		//std::cout << "\n";
//		return true;
//	}
//}
//
//bool GameManager::stalemate(bool player, Board B) {
//	Board temp;				// �x�s�Ȯɪ���
//	std::vector<Chess*> me;	// �ͭx
//	//Position gPosition;		// General position
//	//Position egPosition;	// Enemy General position
//
//	// ��X�ͭx
//	int low;
//	int high;
//	if (player) {  // true 7 ~ 13
//		low = 7;
//		high = 13;
//	}
//	else {		   // false 0 ~ 6
//		low = 0;
//		high = 6;
//	}
//	// �i�J�L����
//	Chess* tmp;
//	for (int i = 0; i < 10; i++) {
//		for (int j = 0; j < 9; j++) {
//			if (board.b[i][j] >= low && board.b[i][j] <= high) {
//				switch (board.b[i][j] % 7) {
//				case 0: {
//					tmp = new General(Position{ i, j }, player);
//					me.push_back(tmp);
//					break;
//				}
//				case 1: {
//					tmp = new Advisor(Position{ i, j }, player);
//					me.push_back(tmp);
//					break;
//				}
//				case 2: {
//					tmp = new Elephant(Position{ i, j }, player);
//					me.push_back(tmp);
//					break;
//				}
//				case 3: {
//					tmp = new Horse(Position{ i, j }, player);
//					me.push_back(tmp);
//					break;
//				}
//				case 4: {
//					tmp = new Chariot(Position{ i, j }, player);
//					me.push_back(tmp);
//					break;
//				}
//				case 5: {
//					tmp = new Cannon(Position{ i, j }, player);
//					me.push_back(tmp);
//					break;
//				}
//				case 6: {
//					tmp = new Soldier(Position{ i, j }, player);
//					me.push_back(tmp);
//					break;
//				}
//				default:
//					break;
//				}
//			}
//		}
//	}
//
//	//
//	for (int it = 0; it < me.size(); it++) {
//		for (int i = 0; i < 10; i++) {
//			for (int j = 0; j < 9; j++) {
//				Position next{ i, j };
//				if (me[it]->id != 0 && me[it]->id != 7) {
//					if (me[it]->move(B, next)) {
//						return false;
//					}
//				}
//				else {
//					if (me[it]->move(B, next)) {
//						Board t = B;
//						t.b[next.y][next.x] = me[it]->id;
//						t.b[me[it]->p.y][me[it]->p.y] = -1;
//						if (!faceToFace(t)) {
//							return false;
//						}
//					}
//				}
//			}
//		}
//	}
//}