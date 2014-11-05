// Andrew Nemec
// CSCE 315-502
// Project 2
// Tree and Node header

#include <list>
#include <limits>
#include "Gamestate.h"

using namespace std;

class Node {
private:
	list<Node*> children;
	Operator* op;
	Gamestate* board;
	int value, alpha, beta, height;
public:
	Node(Gamestate* g, int x, int y, Tile t, int h, int a, int b);
	~Node();
	int minmax();
	int evaluate_node();
	Operator* get_op();
	void set_value(int s);
	int get_value();
	Operator* get_child();
};

class Tree {
private:
	Gamestate* board;
	Node* root;
public:
	Tree(Gamestate* g, int x, int y, Tile t, int h);
	Operator* best_move();
};