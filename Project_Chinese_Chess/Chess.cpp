#include "Chess.h"
#include <algorithm>
using namespace std;
Chess::Chess() {

}

Chess::Chess(bool _type) {
	this->type = _type;
}

Chess::Chess(Position _p, bool _type) {
	this->p.x = _p.x;
	this->p.y = _p.y;
	this->type = _type;
}

void Chess::setPosition(int _x, int _y) {
	this->p.x = _x;
	this->p.y = _y;
}

void Chess::setPosition(Position _p) {
	this->p.x = _p.x;
	this->p.y = _p.y;
}

void Chess::setType(bool _type) {
	this->type = _type;
}



General::General() : Chess() {

}

General::General(bool _type) : Chess(_type) {
	this->p.x = 4;
	if (!_type) {
		this->p.y = 0;
	}
	else {
		this->p.y = 9;
	}
	this->id = 0 + _type * 7;
}

General::General(Position _p, bool _type)
	: Chess(_p, _type) {
	this->p.x = _p.x;
	this->p.y = _p.y;
	this->type = _type;
	this->id = 0 + _type * 7;
}

bool General::move(const Board& board, Position target) {
	if (abs(p.x - target.x) + abs(p.y - target.y) != 1) {
		return false;
	}
	if (target.x > 5 || target.x < 3) {
		return false;
	}
	if (type == 1 && (target.y > 9 || target.y < 7)) {
		return false;
	}
	else if(!type && (target.y > 2 || target.y < 0)){
		return false;
	}
	/*
	Position enemyGeneral;
	for (int i = 0; i < 10; i++) {
		for (int j = 0; j < 9; j++) {
			if ((board.b[i][j] == 0 || board.b[i][j] == 7) && j != p.y && j != p.x) {
				enemyGeneral.x = j;
				enemyGeneral.y = i;
			}
		}
	}
	int yStart = target.y;
	int yEnd = enemyGeneral.y;
	if (target.x == enemyGeneral.x) {
		//std::cout << "5: \n";
		if (yStart > yEnd) {
			swap(yStart, yEnd);
		}
		for (int i = yStart + 1; i < yEnd; i++) {
			//std::cout << B.b[i][g.x] << " ";
			if (board.b[i][target.x] != -1) {
				return true;
			}
		}
		//std::cout << "\n";
		return false;
	}
	*/
	return true;
}

vector<Position> General::canGo() {
	vector<Position> save;
	save.push_back(p);
	int dx[4] = { 1, 0, 0, -1 };
	int dy[4] = { 0, -1, 1, 0 };
	if (type == 1) {
		for (int i = 0; i < 4; i++) {
			int x = this->p.x + dx[i];
			int y = this->p.y + dy[i];
			if (x <= 5 && x >= 3 && y <= 9 && y >= 7) {
				save.push_back({ y,x });
			}
		}
	}
	else {
		for (int i = 0; i < 4; i++) {
			int x = this->p.x + dx[i];
			int y = this->p.y + dy[i];
			if (x <= 5 && x >= 3 && y <= 2 && y >= 0) {
				save.push_back({ y,x });
			}
		}
	}
	return save;
}

Advisor::Advisor() : Chess() {

}

Advisor::Advisor(Position _p, bool _type) 
	: Chess(_p, _type) {
	id = 1;
	this->p.x = _p.x;
	this->p.y = _p.y;
	this->id = 1 + _type * 7;
}

bool Advisor::move(const Board& board, Position target) {
	if (abs((p.x - target.x) * (p.x - target.x)) + abs((p.y - target.y) * (p.y - target.y)) != 2) {
		return false;
	}
	if (target.x > 5 || target.x < 3) {
		return false;
	}
	if (type == 1 && (target.y > 9 || target.y < 7)) {
		return false;
	}
	else if (!type && (target.y > 2 || target.y < 0)) {
		return false;
	}
}

vector<Position> Advisor::canGo() {
	vector<Position> save;
	save.push_back(p);
	int dx[4] = { 1, 1, -1, -1 };
	int dy[4] = { 1, -1, 1, -1 };
	if (type == 1) {
		for (int i = 0; i < 4; i++) {
			int x = this->p.x + dx[i];
			int y = this->p.y + dy[i];
			if (x <= 5 && x >= 3 && y <= 9 && y >= 7) {
				save.push_back({ y,x });
			}
		}
	}
	else {
		for (int i = 0; i < 4; i++) {
			int x = this->p.x + dx[i];
			int y = this->p.y + dy[i];
			if (x <= 5 && x >= 3 && y <= 2 && y >= 0) {
				save.push_back({ y,x });
			}
		}
	}
	return save;
}

Elephant::Elephant() : Chess() {

}

Elephant::Elephant(Position _p, bool _type)
	: Chess(_p, _type) {
	this->id = 2 + _type * 7;
}

bool Elephant::move(const Board& board, Position target) {
	if (abs((p.x - target.x) * (p.x - target.x)) + abs((p.y - target.y) * (p.y - target.y)) != 8) {
		return false;
	}
	if (target.x < 0 || target.y < 0 || target.x > 8 || target.y > 9) {
		return false;
	}
	int midX = (p.x + target.x) / 2;
	int midY = (p.y + target.y) / 2;
	if (board.b[midY][midX] != -1) {
		return false;
	}
	return true;
}

vector<Position> Elephant::canGo() {
	vector<Position> save;
	save.push_back(p);
	int dx[4] = { 2, 2, -2, -2 };
	int dy[4] = { -2, 2, -2, 2 };
	for (int i = 0; i < 4; i++) {
		int x = this->p.x + dx[i];
		int y = this->p.y + dy[i];
		if (x <= 8 && x >= 0 && y <= 9 && y >= 0) {
			save.push_back({ y,x });
		}
	}
	return save;
}

Horse::Horse() : Chess() {

}

Horse::Horse(Position _p, bool _type)
	: Chess(_p, _type) {
	id = 3 + _type * 7;
}

bool Horse::move(const Board& board, Position target) {
	if (abs((p.x - target.x) * (p.x - target.x)) + abs((p.y - target.y) * (p.y - target.y)) != 5) {
		return false;
	}
	if (abs(p.x - target.x) == 2) {
		int midX = (p.x + target.x) / 2;
		if (board.b[p.y][midX] != -1) {
			return false;
		}
	}
	else if (abs(p.y - target.y) == 2) {
		int midY = (p.y + target.y) / 2;
		if (board.b[midY][p.x] != -1) {
			return false;
		}
	}
	return true;
}

vector<Position> Horse::canGo() {
	vector<Position> save;
	save.push_back(p);
	int dx[8] = { 1, 1, -1, -1, 2, 2, -2, -2 };
	int dy[8] = { 2, -2, 2, -2, 1, -1, 1, -1 };
	for (int i = 0; i < 8; i++) {
		int x = this->p.x + dx[i];
		int y = this->p.y + dy[i];
		if (x <= 8 && x >= 0 && y <= 9 && y >= 0) {
			save.push_back({ y,x });
		}
	}
	return save;
}

Chariot::Chariot() : Chess() {

}

Chariot::Chariot(Position _p, bool _type)
	: Chess(_p, _type) {
	this->p.x = _p.x;
	this->p.y = _p.y;
	this->type = _type;
	id = 4 + _type * 7;
}

bool Chariot::move(const Board& board, Position target) {
	if (abs(p.x - target.x) && abs(p.y - target.y)) {
		return false;
	}
	if (target.x < 0 || target.y < 0 || target.x > 8 || target.y > 9) {
		return false;
	}
	if (abs(p.x - target.x)) {
		int sm = std::min(p.x, target.x);
		int bg = std::max(p.x, target.x);
		for (int i = sm + 1; i < bg; i++) {
			if (board.b[p.y][i] != -1) {
				return false;
			}
		}
	}
	else if (abs(p.y - target.y)) {
		int sm = std::min(p.y, target.y);
		int bg = std::max(p.y, target.y);
		for (int i = sm + 1; i < bg; i++) {
			if (board.b[i][p.x] != -1) {
				return false;
			}
		}
	}
	return true;
}

vector<Position> Chariot::canGo() {
	vector<Position> save;
	save.push_back(p);
	for (int i = 0; i < 10; i++) {
		int x = this->p.x + i;
		int y = this->p.y;
		if (x <= 8 && x >= 0 && y <= 9 && y >= 0) {
			save.push_back({ y,x });
		}
		x = this->p.x - i;
		y = this->p.y;
		if (x <= 8 && x >= 0 && y <= 9 && y >= 0) {
			save.push_back({ y,x });
		}
		x = this->p.x;
		y = this->p.y + i;
		if (x <= 8 && x >= 0 && y <= 9 && y >= 0) {
			save.push_back({ y,x });
		}
		x = this->p.x;
		y = this->p.y - i;
		if (x <= 8 && x >= 0 && y <= 9 && y >= 0) {
			save.push_back({ y,x });
		}
	}
	return save;
}

Cannon::Cannon() : Chess() {

}

Cannon::Cannon(Position _p, bool _type)
	: Chess(_p, _type) {
	id = 5 + _type * 7;
}

bool Cannon::move(const Board& board, Position target) {
	if (!abs(p.x - target.x) && !abs(p.y - target.y)) {
		return false;
	}
	if (abs(p.x - target.x) && abs(p.y - target.y)) {
		return false;
	}
	if (board.b[target.y][target.x] != -1) {
		int count = 0;
		if (p.y > target.y) {
			for (int i = p.y - 1; i > target.y; i--) {
				if (board.b[i][p.x] != -1) count++;
				if (count >= 2) return false;
			}
			if (!count) return false;
		}
		else if (p.y < target.y) {
			for (int i = p.y + 1; i < target.y; i++) {
				if (board.b[i][p.x] != -1) count++;
				if (count >= 2) return false;
			}
			if (!count) return false;
		}
		else if (p.x > target.x) {
			for (int i = p.x - 1; i > target.x; i--) {
				if (board.b[p.y][i] != -1) count++;
				if (count >= 2) return false;
			}
			if (!count) return false;
		}
		else if (p.x < target.x) {
			for (int i = p.x + 1; i < target.x; i++) {
				if (board.b[p.y][i] != -1) count++;
				if (count >= 2) return false;
			}
			if (!count) return false;
		}
	}
	else {
		if (p.y > target.y) {
			for (int i = p.y - 1; i > target.y; i--) {
				if (board.b[i][p.x] != -1) return false;
			}
		}
		else if (p.y < target.y) {
			for (int i = p.y + 1; i < target.y; i++) {
				if (board.b[i][p.x] != -1) return false;
			}
		}
		else if (p.x > target.x) {
			for (int i = p.x - 1; i > target.x; i--) {
				if (board.b[p.y][i] != -1) return false;
			}
		}
		else if (p.x < target.x) {
			for (int i = p.x + 1; i < target.x; i++) {
				if (board.b[p.y][i] != -1) return false;
			}
		}
	}
	return true;
}

vector<Position> Cannon::canGo() {
	vector<Position> save;
	save.push_back(p);
	for (int i = 0; i < 10; i++) {
		int x = this->p.x + i;
		int y = this->p.y;
		if (x <= 8 && x >= 0 && y <= 9 && y >= 0) {
			save.push_back({ y,x });
		}
		x = this->p.x - i;
		y = this->p.y;
		if (x <= 8 && x >= 0 && y <= 9 && y >= 0) {
			save.push_back({ y,x });
		}
		x = this->p.x;
		y = this->p.y + i;
		if (x <= 8 && x >= 0 && y <= 9 && y >= 0) {
			save.push_back({ y,x });
		}
		x = this->p.x;
		y = this->p.y - i;
		if (x <= 8 && x >= 0 && y <= 9 && y >= 0) {
			save.push_back({ y,x });
		}
	}
	return save;
}

Soldier::Soldier() : Chess() {

}

Soldier::Soldier(Position _p, bool _type)
	: Chess(_p, _type) {
	id = 6 + _type * 7;
}

bool Soldier::move(const Board& board, Position target) {
	if (abs(p.x - target.x) + abs(p.y - target.y) != 1) {
		return false;
	}
	if (target.x < 0 || target.y < 0 || target.x > 8 || target.y > 9) {
		return false;
	}
	if (type == 1) {
		if(p.y > 4 && p.x != target.x || p.y < target.y)
			return false;
	}
	if (type == 0){
		if(p.y < 5 && p.x != target.x || p.y > target.y)
			return false;
	}
	return true;
}

vector<Position> Soldier::canGo() {
	vector<Position> save;
	save.push_back(p);
	if (type == 1) {
		if (p.y < 5) {
			int x = this->p.x;
			int y = this->p.y - 1;
			if (x <= 8 && x >= 0 && y <= 9 && y >= 0) {
				save.push_back({ y,x });
			}
			x = this->p.x + 1;
			y = this->p.y;
			if (x <= 8 && x >= 0 && y <= 9 && y >= 0) {
				save.push_back({ y,x });
			}
			x = this->p.x - 1;
			y = this->p.y;
			if (x <= 8 && x >= 0 && y <= 9 && y >= 0) {
				save.push_back({ y,x });
			}
		}
		else {
			int x = this->p.x;
			int y = this->p.y - 1;
			if (x <= 8 && x >= 0 && y <= 9 && y >= 0) {
				save.push_back({ y,x });
			}
		}
		
	}
	else {
		if (p.y > 4) {
			int x = this->p.x;
			int y = this->p.y + 1;
			if (x <= 8 && x >= 0 && y <= 9 && y >= 0) {
				save.push_back({ y,x });
			}
			x = this->p.x + 1;
			y = this->p.y;
			if (x <= 8 && x >= 0 && y <= 9 && y >= 0) {
				save.push_back({ y,x });
			}
			x = this->p.x - 1;
			y = this->p.y;
			if (x <= 8 && x >= 0 && y <= 9 && y >= 0) {
				save.push_back({ y,x });
			}
		} 
		else {
			int x = this->p.x;
			int y = this->p.y + 1;
			if (x <= 8 && x >= 0 && y <= 9 && y >= 0) {
				save.push_back({ y,x });
			}
		}
	}
	return save;
}