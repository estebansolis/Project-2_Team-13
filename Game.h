// Andrew Nemec
// CSCE 315-502
// Project 2
// Game Header
#pragma once


#include <stack>
#include <stdlib.h>
#include <time.h>
#include "Gamestate.h"

using namespace std;

class Game {
private:
	Gamestate game;
	stack<Operator*> previous_moves;
public:
	void undo();
	int make_move(char t, int x, int y);
	int random_int();
	void print_to_screen();
	//string easy_ai(Operator op);
};