// Andrew Nemec
// CSCE 315-502
// Project 2
// Gamestate Implementation

#include "Gamestate.h"

Gamestate::Gamestate() {
	for (int i = 0; i < 15; ++i) {
		vector<Tile> t;
		for (int j = 0; j < 15; ++j) {
			t.push_back(empty);
		}
		board.push_back(t);
	}
}

bool Gamestate::is_legal(Operator* op) {
	pair<int, int> p = op->get_coordinate();
	Tile t = op->get_tile();
	vector<Tile> vertical, horizontal, maj_diag, min_diag;
	
	if (board[p.second - 1][p.first - 1] != empty) {
		return false;
	}
	
	for (int i = 0; i < 15; ++i) {
		vertical.push_back(board[i][p.first - 1]);
	}
	
	for (int i = 0; i < 15; ++i) {
		horizontal.push_back(board[p.second - 1][i]);
	}
	
	int i = p.first - min(p.first, p.second) , j = p.second - min(p.first, p.second);
	for (i, j; (i < 15) && (j < 15); ++i, ++j) {
		maj_diag.push_back(board[j][i]);
	}
	
	i = p.first, j = p.second;
	while ((i < 15) && (j > 0)) {
		++i;
		--j;
	}
	for (i, j; (i < 15) && (j > 0); ++i, --j) {
		min_diag.push_back(board[j][i]);
	}
	
	int h = 0;
	while (!vertical.empty()) {
		if (vertical.back() == t) {
			++h;
		}
		else {
			h = 0;
		}
		if (h == 6) {
			return false;
		}
		vertical.pop_back();
	}
	
	h = 0;
	while (!horizontal.empty()) {
		if (horizontal.back() == t) {
			++h;
		}
		else {
			h = 0;
		}
		if (h == 6) {
			return false;
		}
		horizontal.pop_back();
	}
	
	h = 0;
	while (!maj_diag.empty()) {
		if (maj_diag.back() == t) {
			++h;
		}
		else {
			h = 0;
		}
		if (h == 6) {
			return false;
		}
		maj_diag.pop_back();
	}
	
	h = 0;
	while (!min_diag.empty()) {
		if (min_diag.back() == t) {
			++h;
		}
		else {
			h = 0;
		}
		if (h == 6) {
			return false;
		}
		min_diag.pop_back();
	}
	
	if ((p.second > 3) && (t == board[p.second - 2][p.first - 1]) && (t == board[p.second - 3][p.first - 1]) && (empty == board[p.second - 4][p.first - 1])) {
		if ((p.first > 3) && (t == board[p.second - 2][p.first - 2]) && (t == board[p.second - 3][p.first - 3]) && (empty == board[p.second - 4][p.first - 4])) {
			return false;
		}
		if ((p.first > 3) && (t == board[p.second - 1][p.first - 2]) && (t == board[p.second - 1][p.first - 3]) && (empty == board[p.second - 1][p.first - 4])) {
			return false;
		}
		if ((p.first > 3) && (p.second < 12) && (t == board[p.second][p.first - 2]) && (t == board[p.second + 1][p.first - 3]) && (empty == board[p.second + 2][p.first - 4])) {
			return false;
		}
		if ((p.first < 12) && (p.second < 12) && (t == board[p.second][p.first]) && (t == board[p.second + 1][p.first + 1]) && (empty == board[p.second + 2][p.first + 3])) {
			return false;
		}
		if ((p.first < 12) && (t == board[p.second - 1][p.first]) && (t == board[p.second - 1][p.first + 1]) && (empty == board[p.second - 1][p.first + 2])) {
			return false;
		}
		if ((p.first < 12) && (t == board[p.second - 2][p.first]) && (t == board[p.second - 3][p.first + 1]) && (empty == board[p.second - 4][p.first + 2])) {
			return false;
		}
	}
	
	if ((p.second > 3) && (p.first > 3) && (t == board[p.second - 2][p.first - 2]) && (t == board[p.second - 3][p.first - 3]) && (empty == board[p.second - 4][p.first - 4])) {
		if ((t == board[p.second - 1][p.first - 2]) && (t == board[p.second - 1][p.first - 3]) && (empty == board[p.second - 1][p.first - 4])) {
			return false;
		}
		if ((p.second < 12) && (t == board[p.second][p.first - 2]) && (t == board[p.second + 1][p.first - 3]) && (empty == board[p.second + 2][p.first - 4])) {
			return false;
		}
		if ((p.second < 12) && (t == board[p.second][p.first - 1]) && (t == board[p.second + 1][p.first - 1]) && (empty == board[p.second + 2][p.first - 1])) {
			return false;
		}
		if ((p.first < 12) && (t == board[p.second - 1][p.first]) && (t == board[p.second - 1][p.first + 1]) && (empty == board[p.second - 1][p.first + 2])) {
			return false;
		}
		if ((p.first < 12) && (t == board[p.second - 2][p.first]) && (t == board[p.second - 3][p.first + 1]) && (empty == board[p.second - 4][p.first + 2])) {
			return false;
		}
	}
	
	if ((p.first > 3) && (t == board[p.second - 1][p.first - 2]) && (t == board[p.second - 1][p.first - 3]) && (empty == board[p.second - 1][p.first - 4])) {
		if ((p.second < 12) && (t == board[p.second][p.first - 2]) && (t == board[p.second + 1][p.first - 3]) && (empty == board[p.second + 2][p.first - 4])) {
			return false;
		}
		if ((p.second < 12) && (t == board[p.second][p.first - 1]) && (t == board[p.second + 1][p.first - 1]) && (empty == board[p.second + 2][p.first - 1])) {
			return false;
		}
		if ((p.second < 12) && (p.first < 12) && (t == board[p.second][p.first]) && (t == board[p.second + 1][p.first + 1]) && (empty == board[p.second + 2][p.first + 1])) {
			return false;
		}
		if ((p.second > 3) && (p.first < 12) && (t == board[p.second - 2][p.first]) && (t == board[p.second - 3][p.first + 1]) && (empty == board[p.second - 4][p.first + 2])) {
			return false;
		}
	}
	
	if ((p.first > 3) && (p.second < 12) && (t == board[p.second][p.first - 2]) && (t == board[p.second + 1][p.first - 3]) && (empty == board[p.second + 2][p.first - 4])) {
		if ((t == board[p.second][p.first - 1]) && (t == board[p.second + 1][p.first - 1]) && (empty == board[p.second + 2][p.first - 1])) {
			return false;
		}
		if ((p.first < 12) && (t == board[p.second][p.first]) && (t == board[p.second + 1][p.first + 1]) && (empty == board[p.second + 2][p.first + 1])) {	
			return false;
		}
		if ((p.first < 12) && (t == board[p.second - 1][p.first]) && (t == board[p.second - 1][p.first + 1]) && (empty == board[p.second - 1][p.first + 2])) {
			return false;
		}
	}
	
	if ((p.second < 12) && (t == board[p.second][p.first - 1]) && (t == board[p.second + 1][p.first - 1]) && (empty == board[p.second + 2][p.first - 1])) {
		if ((p.first < 12) && (t == board[p.second][p.first]) && (t == board[p.second + 1][p.first + 1]) && (empty == board[p.second + 2][p.first + 2])) {
			return false;
		}
		if ((p.first < 12) && (t == board[p.second - 1][p.first]) && (t == board[p.second - 1][p.first + 1]) && (empty == board[p.second - 1][p.first + 2])) {
			return false;
		}
		if ((p.first < 12) && (p.second > 3) && (t == board[p.second - 2][p.first]) && (t == board[p.second - 3][p.first + 1]) && (empty == board[p.second - 4][p.first + 2])) {
			return false;
		}
	}
	
	if ((p.first < 12) && (p.second < 12) && (t == board[p.second][p.first]) && (t == board[p.second + 1][p.first + 1]) && (empty == board[p.second + 2][p.first + 2])) {
		if ((t == board[p.second - 1][p.first]) && (t == board[p.second - 1][p.first + 1]) && (empty == board[p.second - 1][p.first + 2])) {
			return false;
		}
		if ((p.second > 3) && (t == board[p.second - 2][p.first]) && (t == board[p.second - 3][p.first + 1]) && (empty == board[p.second - 4][p.first + 2])) {
			return false;
		}
	}
	
	if ((p.first < 12) && (t == board[p.second - 1][p.first]) && (t == board[p.second - 1][p.first + 1]) && (empty == board[p.second - 1][p.first + 2])) {
		if ((p.second > 3) && (t == board[p.second - 2][p.first]) && (t == board[p.second - 3][p.first + 1]) && (empty == board[p.second - 4][p.first + 2])) {
			return false;
		}
	}
	
	return true;
}

void Gamestate::print_to_screen() {
	cout << ";  1 2 3 4 5 6 7 8 9 a b c d e f\n";
	for (int i = 0; i < 15; ++i) {
		cout << ";" << hex << (i + 1) << dec;
		for (int j = 0; j < 15; ++j) {
			Tile t = board[i][j];
			switch (t) {
				case empty:
					cout << " +";
					break;
				case black:
					cout << " @";
					break;
				case white:
					cout << " 0";
					break;
			}
		}
		cout << "\n";
	}
}

bool Gamestate::make_move(Operator* op) {
	if (is_legal(op)) {
		pair<int, int> p = op->get_coordinate();
		board[p.second - 1][p.first - 1] = op->get_tile();
		return true;
	}
	else {
		return false;
	}
}

bool Gamestate::remove_move(Operator* op) {
	pair<int, int> p = op->get_coordinate();
	Tile t = op->get_tile();
	if (board[p.second - 1][p.first - 1] == t) {
		board[p.second - 1][p.first - 1] = empty;
		return true;
	}
	else {
		return false;
	}
}

bool Gamestate::is_victory(Operator* op) {
	pair<int, int> p = op->get_coordinate();
	Tile t = op->get_tile();
	vector<Tile> vertical, horizontal, maj_diag, min_diag;
	
	for (int i = 0; i < 15; ++i) {
		vertical.push_back(board[i][p.first - 1]);
	}
	
	for (int i = 0; i < 15; ++i) {
		horizontal.push_back(board[p.second - 1][i]);
	}
	
	int i = p.first - min(p.first, p.second) , j = p.second - min(p.first, p.second);
	for (i, j; (i < 15) && (j < 15); ++i, ++j) {
		maj_diag.push_back(board[j][i]);
	}
	
	i = p.first, j = p.second;
	while ((i < 15) && (j > 0)) {
		++i;
		--j;
	}
	for (i, j; (i < 15) && (j > 0); ++i, --j) {
		min_diag.push_back(board[j][i]);
	}
	
	int h = 0;
	while (!vertical.empty()) {
		if (vertical.back() == t) {
			++h;
		}
		else {
			h = 0;
		}
		if (h == 5) {
			return true;
		}
		vertical.pop_back();
	}
	
	h = 0;
	while (!horizontal.empty()) {
		if (horizontal.back() == t) {
			++h;
		}
		else {
			h = 0;
		}
		if (h == 5) {
			return true;
		}
		horizontal.pop_back();
	}
	
	h = 0;
	while (!maj_diag.empty()) {
		if (maj_diag.back() == t) {
			++h;
		}
		else {
			h = 0;
		}
		if (h == 5) {
			return true;
		}
		maj_diag.pop_back();
	}
	
	h = 0;
	while (!min_diag.empty()) {
		if (min_diag.back() == t) {
			++h;
		}
		else {
			h = 0;
		}
		if (h == 5) {
			return true;
		}
		min_diag.pop_back();
	}
	
	return false;
}

Tile Gamestate::get_element(int x, int y) {
	return board[y][x];
}
/* 
int main() {
	Gamestate g;
	Operator o = Operator(1, 1, white);
	Operator p = Operator(6, 2, black);
	g.make_move(o);
	g.make_move(p);
	g.print_to_screen();
	return 0;
} */