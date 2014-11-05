// Andrew Nemec
// CSCE 315-502
// Project 2
// Gamestate Header

#pragma once

#include <vector>
#include <iostream>
#include <stack>
#include "Operator.h"

using namespace std;

class Gamestate {
private:
	vector<vector<Tile>> board;
public:
	Gamestate();
	bool is_legal(Operator* op);
	void print_to_screen();
	bool make_move(Operator* op);
	bool remove_move(Operator* op);
	bool is_victory(Operator* op);
	Tile get_element(int x, int y);
};