#pragma once
#include <iostream>
#include <vector>
struct Position {
	int y = 0;
	int x = 0;
	inline bool operator==(Position a) {
		if (a.x == x && a.y == y)
			return true;
		else
			return false;
	}
};

class Board {
public:
	int b[10][9];
public:
	Board() {
		for (int i = 0; i < 10; i++) {
			for (int j = 0; j < 9; j++) {
				b[i][j] = -1;
			}
		}
		/*
		b = new Chess * [10];
		for (int i = 0; i < 10; i++) {
			b[i] = new Chess[9];
		}
		for (int i = 0; i < 10; i++) {
			for (int j = 0; j < 9; j++) {
				b[i][j] = new Chess();
			}
		}
		*/
	}
	void restart() {
		for (int i = 0; i < 10; i++) {
			for (int j = 0; j < 9; j++) {
				b[i][j] = -1;
			}
		}
	}
};

class Chess
{
public:
	Position p;
	bool type;
	int id = -1;
	//std::vector<Position> step;
public:
	Chess();
	Chess(bool _type);
	Chess(Position _p, bool _type);
	void setPosition(int _x, int _y);
	void setPosition(Position _p);
	Position getPosition() { return this->p; }
	void setType(bool _type);
	bool getType() { return this->type; }
	int getID() { return this->id; }
	virtual bool move(const Board& board, Position target) { std::cout << "1"; return false; };
	virtual std::vector<Position> canGo() { std::vector<Position> a; return a; };
};

class General : public Chess
{
public:
	General();
	General(bool _type);
	General(Position _p, bool _type);
	int getID() { return this->id; }
	bool move(const Board& board, Position target) override;
	std::vector<Position> canGo() override;
};

class Advisor : public Chess
{
public:
public:
	Advisor();
	Advisor(Position _p, bool _type);
	int getID() { return this->id; }
	bool move(const Board& board, Position target);
	std::vector<Position> canGo() override;
};

class Elephant : public Chess
{
public:
public:
	Elephant();
	Elephant(Position _p, bool _type);
	int getID() { return this->id; }
	bool move(const Board& board, Position target);
	std::vector<Position> canGo() override;
};

class Horse : public Chess
{
public:
public:
	Horse();
	Horse(Position _p, bool _type);
	int getID() { return this->id; }
	bool move(const Board& board, Position target);
	std::vector<Position> canGo() override;
};

class Chariot : public Chess
{
public:
public:
	Chariot();
	Chariot(Position _p, bool _type);
	int getID() { return this->id; }
	bool move(const Board& board, Position target);
	std::vector<Position> canGo() override;
};

class Cannon : public Chess
{
public:
public:
	Cannon();
	Cannon(Position _p, bool _type);
	int getID() { return this->id; }
	bool move(const Board& board, Position target);
	std::vector<Position> canGo() override;
};

class Soldier : public Chess
{
public:
public:
	Soldier();
	Soldier(Position _p, bool _type);
	int getID() { return this->id; }
	bool move(const Board& board, Position target);
	std::vector<Position> canGo() override;
};