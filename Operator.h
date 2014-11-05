// Andrew Nemec
// CSCE 315-502
// Project 2
// Operator Header
#pragma once

#include <utility>

using namespace std;

enum Tile { empty, black, white};

class Operator {
private:
	pair<int, int> coordinate;
	Tile tile;
public:
	Operator(int x, int y, Tile t) : coordinate(make_pair(x, y)), tile(t) {}
	pair<int, int> get_coordinate();
	Tile get_tile();
};