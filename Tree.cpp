// Andrew Nemec
// CSCE 315-502
// Project 2
// Tree and Node Implementation

#include "Tree.h"

Node::Node(Gamestate* g, int x, int y, Tile t, int h, int a, int b) {
	board = g;
	op = new Operator(x, y, t);
	if (t == white) {
		value = numeric_limits<int>::max();
	}
	else {
		value = numeric_limits<int>::min();
	}
	height = h;
	alpha = a;
	beta = b;
}

Node::~Node() {
	while (!children.empty()) {
		Node* n = children.front();
		children.pop_front();
		delete n;
	}
	delete op;
}

int Node::minmax() {
	if (height == 0) {
		return evaluate_node();
	}
	
	if (op->get_tile() == black) {
		for (int i = 1; i <= 15; ++i) {
			for (int j = 1; j <= 15; ++j) {
				Node* n = new Node(board, i, j, white, height - 1, alpha, beta);
				if (board->is_legal(n->get_op())) {
					board->make_move(n->get_op());
					int v = n->minmax();
					// cerr << "token: white (" << height - 1 << ")   (" << i << "," << j << ")   value: " << v << "   alpha: " << alpha << "   beta: " << beta << '\n';
					if (v >= beta) {
						value = beta;
						children.push_back(n);
						board->remove_move(n->get_op());
						return beta;
					}
					if (v > alpha) {
						alpha = v;
						value = v;
						children.push_back(n);
					}
					board->remove_move(n->get_op());
				}
				else {
					delete n;
				}
			}
		}
		return alpha;
	}
	else {
		for (int i = 1; i <= 15; ++i) {
			for (int j = 1; j <= 15; ++j) {
				Node* n = new Node(board, i, j, black, height - 1, alpha, beta);
				if (board->is_legal(n->get_op())) {
					board->make_move(n->get_op());
					int v = n->minmax();
					// cerr << "token: black (" << height - 1 << ")   (" << i << "," << j << ")   value: " << v << "   alpha: " << alpha << "   beta: " << beta << '\n';
					if (v <= alpha) {
						value = alpha;
						children.push_back(n);
						board->remove_move(n->get_op());
						return alpha;
					}
					if (v < beta) {
						beta = v;
						value = v;
						children.push_back(n);
					}
					board->remove_move(n->get_op());
				}
				else {
					delete n;
				}
			}
		}
		return beta;
	}
}

int Node::evaluate_node() {
	pair<int, int> m = op->get_coordinate();
	int xx = m.first - 1, yy = m.second - 1;
	Tile t = op->get_tile();
	// cerr << "t = " << t << "   xx = " << xx << "   yy = " << yy << '\n';
	
	// Check for winning move
	if (board->is_victory(op)) {
		if (t == black) {
			return numeric_limits<int>::max();
		}
		else {
			return numeric_limits<int>::min();
		}
	}
	
	board->make_move(op);
	
	// Block a winning move
	if (t == black) {
		if ((yy >= 4) && (board->get_element(xx, yy - 1) == white) && (board->get_element(xx, yy - 2) == white) && (board->get_element(xx, yy - 3) == white) && (board->get_element(xx, yy - 4) == white)) {
			board->remove_move(op);
			return 50;
		}
		if ((yy >= 4) && (xx >= 4) && (board->get_element(xx - 1, yy - 1) == white) && (board->get_element(xx - 2, yy - 2) == white) && (board->get_element(xx - 3, yy - 3) == white) && (board->get_element(xx - 4, yy - 4) == white)) {
			board->remove_move(op);
			return 50;
		}
		if ((xx >= 4) && (board->get_element(xx - 1, yy) == white) && (board->get_element(xx - 2, yy) == white) && (board->get_element(xx - 3, yy) == white) && (board->get_element(xx - 4, yy) == white)) {
			board->remove_move(op);
			return 50;
		}
		if ((yy <= 10) && (xx >= 4) && (board->get_element(xx - 1, yy + 1) == white) && (board->get_element(xx - 2, yy + 2) == white) && (board->get_element(xx - 3, yy + 3) == white) && (board->get_element(xx - 4, yy + 4) == white)) {
			board->remove_move(op);
			return 50;
		}
		if ((yy <= 10) && (board->get_element(xx, yy + 1) == white) && (board->get_element(xx, yy + 2) == white) && (board->get_element(xx, yy + 3) == white) && (board->get_element(xx, yy + 4) == white)) {
			board->remove_move(op);
			return 50;
		}
		if ((yy <= 10) && (xx <= 10) && (board->get_element(xx + 1, yy + 1) == white) && (board->get_element(xx + 2, yy + 2) == white) && (board->get_element(xx + 3, yy + 3) == white) && (board->get_element(xx + 4, yy + 4) == white)) {
			board->remove_move(op);
			return 50;
		}
		if ((xx <= 10) && (board->get_element(xx + 1, yy) == white) && (board->get_element(xx + 2, yy) == white) && (board->get_element(xx + 3, yy) == white) && (board->get_element(xx + 4, yy) == white)) {
			board->remove_move(op);
			return 50;
		}
		if ((yy >= 4) && (xx <= 10) && (board->get_element(xx + 1, yy - 1) == white) && (board->get_element(xx + 2, yy - 2) == white) && (board->get_element(xx + 3, yy - 3) == white) && (board->get_element(xx + 4, yy + 4) == white)) {
			board->remove_move(op);
			return 50;
		}
	}
	else {
		if ((yy >= 4) && (board->get_element(xx, yy - 1) == black) && (board->get_element(xx, yy - 2) == black) && (board->get_element(xx, yy - 3) == black) && (board->get_element(xx, yy - 4) == black)) {
			board->remove_move(op);
			return -50;
		}
		if ((yy >= 4) && (xx >= 4) && (board->get_element(xx - 1, yy - 1) == black) && (board->get_element(xx - 2, yy - 2) == black) && (board->get_element(xx - 3, yy - 3) == black) && (board->get_element(xx - 4, yy - 4) == black)) {
			board->remove_move(op);
			return -50;
		}
		if ((xx >= 4) && (board->get_element(xx - 1, yy) == black) && (board->get_element(xx - 2, yy) == black) && (board->get_element(xx - 3, yy) == black) && (board->get_element(xx - 4, yy) == black)) {
			board->remove_move(op);
			return -50;
		}
		if ((yy <= 10) && (xx >= 4) && (board->get_element(xx - 1, yy + 1) == black) && (board->get_element(xx - 2, yy + 2) == black) && (board->get_element(xx - 3, yy + 3) == black) && (board->get_element(xx - 4, yy + 4) == black)) {
			board->remove_move(op);
			return -50;
		}
		if ((yy <= 10) && (board->get_element(xx, yy + 1) == black) && (board->get_element(xx, yy + 2) == black) && (board->get_element(xx, yy + 3) == black) && (board->get_element(xx, yy + 4) == black)) {
			board->remove_move(op);
			return -50;
		}
		if ((yy <= 10) && (xx <= 10) && (board->get_element(xx + 1, yy + 1) == black) && (board->get_element(xx + 2, yy + 2) == black) && (board->get_element(xx + 3, yy + 3) == black) && (board->get_element(xx + 4, yy + 4) == black)) {
			board->remove_move(op);
			return -50;
		}
		if ((xx <= 10) && (board->get_element(xx + 1, yy) == black) && (board->get_element(xx + 2, yy) == black) && (board->get_element(xx + 3, yy) == black) && (board->get_element(xx + 4, yy) == black)) {
			board->remove_move(op);
			return -50;
		}
		if ((yy >= 4) && (xx <= 10) && (board->get_element(xx + 1, yy - 1) == black) && (board->get_element(xx + 2, yy - 2) == black) && (board->get_element(xx + 3, yy - 3) == black) && (board->get_element(xx + 4, yy + 4) == black)) {
			board->remove_move(op);
			return -50;
		}
	}
	
	// Create a 4 on 4
	if (t == black) {
		int f = 0;
		if ((yy >= 3) && (board->get_element(xx, yy - 1) == black) && (board->get_element(xx, yy - 2) == black) && (board->get_element(xx, yy - 3) == black)) {
			++f;
		}
		if ((yy >= 3) && (xx >= 3) && (board->get_element(xx - 1, yy - 1) == black) && (board->get_element(xx - 2, yy - 2) == black) && (board->get_element(xx - 3, yy - 3) == black)) {
			++f;
		}
		if ((xx >= 3) && (board->get_element(xx - 1, yy) == black) && (board->get_element(xx - 2, yy) == black) && (board->get_element(xx - 3, yy) == black)) {
			++f;
		}
		if ((yy <= 11) && (xx >= 3) && (board->get_element(xx - 1, yy + 1) == black) && (board->get_element(xx - 2, yy + 2) == black) && (board->get_element(xx - 3, yy + 3) == black)) {
			++f;
		}
		if ((yy <= 11) && (board->get_element(xx, yy + 1) == black) && (board->get_element(xx, yy + 2) == black) && (board->get_element(xx, yy + 3) == black)) {
			++f;
		}
		if ((yy <= 11) && (xx <= 11) && (board->get_element(xx + 1, yy + 1) == black) && (board->get_element(xx + 2, yy + 2) == black) && (board->get_element(xx + 3, yy + 3) == black)) {
			++f;
		}
		if ((xx <= 11) && (board->get_element(xx + 1, yy) == black) && (board->get_element(xx + 2, yy) == black) && (board->get_element(xx + 3, yy) == black)) {
			++f;
		}
		if ((yy >= 3) && (xx <= 11) && (board->get_element(xx + 1, yy - 1) == black) && (board->get_element(xx + 2, yy - 2) == black) && (board->get_element(xx + 3, yy - 3) == black)) {
			++f;
		}
		if (f > 1) {
			board->remove_move(op);
			return 40;
		}
	}
	else {
		int f = 0;
		if ((yy >= 3) && (board->get_element(xx, yy - 1) == white) && (board->get_element(xx, yy - 2) == white) && (board->get_element(xx, yy - 3) == white)) {
			++f;
		}
		if ((yy >= 3) && (xx >= 3) && (board->get_element(xx - 1, yy - 1) == white) && (board->get_element(xx - 2, yy - 2) == white) && (board->get_element(xx - 3, yy - 3) == white)) {
			++f;
		}
		if ((xx >= 3) && (board->get_element(xx - 1, yy) == white) && (board->get_element(xx - 2, yy) == white) && (board->get_element(xx - 3, yy) == white)) {
			++f;
		}
		if ((yy <= 11) && (xx >= 3) && (board->get_element(xx - 1, yy + 1) == white) && (board->get_element(xx - 2, yy + 2) == white) && (board->get_element(xx - 3, yy + 3) == white)) {
			++f;
		}
		if ((yy <= 11) && (board->get_element(xx, yy + 1) == white) && (board->get_element(xx, yy + 2) == white) && (board->get_element(xx, yy + 3) == white)) {
			++f;
		}
		if ((yy <= 11) && (xx <= 11) && (board->get_element(xx + 1, yy + 1) == white) && (board->get_element(xx + 2, yy + 2) == white) && (board->get_element(xx + 3, yy + 3) == white)) {
			++f;
		}
		if ((xx <= 11) && (board->get_element(xx + 1, yy) == white) && (board->get_element(xx + 2, yy) == white) && (board->get_element(xx + 3, yy) == white)) {
			++f;
		}
		if ((yy >= 3) && (xx <= 11) && (board->get_element(xx + 1, yy - 1) == white) && (board->get_element(xx + 2, yy - 2) == white) && (board->get_element(xx + 3, yy - 3) == white)) {
			++f;
		}
		if (f > 1) {
			board->remove_move(op);
			return -40;
		}
	}
	
	// Block 4 on 4
	if (t == white) {
		int f = 0;
		if ((yy >= 3) && (board->get_element(xx, yy - 1) == black) && (board->get_element(xx, yy - 2) == black) && (board->get_element(xx, yy - 3) == black)) {
			++f;
		}
		if ((yy >= 3) && (xx >= 3) && (board->get_element(xx - 1, yy - 1) == black) && (board->get_element(xx - 2, yy - 2) == black) && (board->get_element(xx - 3, yy - 3) == black)) {
			++f;
		}
		if ((xx >= 3) && (board->get_element(xx - 1, yy) == black) && (board->get_element(xx - 2, yy) == black) && (board->get_element(xx - 3, yy) == black)) {
			++f;
		}
		if ((yy <= 11) && (xx >= 3) && (board->get_element(xx - 1, yy + 1) == black) && (board->get_element(xx - 2, yy + 2) == black) && (board->get_element(xx - 3, yy + 3) == black)) {
			++f;
		}
		if ((yy <= 11) && (board->get_element(xx, yy + 1) == black) && (board->get_element(xx, yy + 2) == black) && (board->get_element(xx, yy + 3) == black)) {
			++f;
		}
		if ((yy <= 11) && (xx <= 11) && (board->get_element(xx + 1, yy + 1) == black) && (board->get_element(xx + 2, yy + 2) == black) && (board->get_element(xx + 3, yy + 3) == black)) {
			++f;
		}
		if ((xx <= 11) && (board->get_element(xx + 1, yy) == black) && (board->get_element(xx + 2, yy) == black) && (board->get_element(xx + 3, yy) == black)) {
			++f;
		}
		if ((yy >= 3) && (xx <= 11) && (board->get_element(xx + 1, yy - 1) == black) && (board->get_element(xx + 2, yy - 2) == black) && (board->get_element(xx + 3, yy - 3) == black)) {
			++f;
		}
		if (f > 1) {
			board->remove_move(op);
			return -35;
		}
	}
	else {
		int f = 0;
		if ((yy >= 3) && (board->get_element(xx, yy - 1) == white) && (board->get_element(xx, yy - 2) == white) && (board->get_element(xx, yy - 3) == white)) {
			++f;
		}
		if ((yy >= 3) && (xx >= 3) && (board->get_element(xx - 1, yy - 1) == white) && (board->get_element(xx - 2, yy - 2) == white) && (board->get_element(xx - 3, yy - 3) == white)) {
			++f;
		}
		if ((xx >= 3) && (board->get_element(xx - 1, yy) == white) && (board->get_element(xx - 2, yy) == white) && (board->get_element(xx - 3, yy) == white)) {
			++f;
		}
		if ((yy <= 11) && (xx >= 3) && (board->get_element(xx - 1, yy + 1) == white) && (board->get_element(xx - 2, yy + 2) == white) && (board->get_element(xx - 3, yy + 3) == white)) {
			++f;
		}
		if ((yy <= 11) && (board->get_element(xx, yy + 1) == white) && (board->get_element(xx, yy + 2) == white) && (board->get_element(xx, yy + 3) == white)) {
			++f;
		}
		if ((yy <= 11) && (xx <= 11) && (board->get_element(xx + 1, yy + 1) == white) && (board->get_element(xx + 2, yy + 2) == white) && (board->get_element(xx + 3, yy + 3) == white)) {
			++f;
		}
		if ((xx <= 11) && (board->get_element(xx + 1, yy) == white) && (board->get_element(xx + 2, yy) == white) && (board->get_element(xx + 3, yy) == white)) {
			++f;
		}
		if ((yy >= 3) && (xx <= 11) && (board->get_element(xx + 1, yy - 1) == white) && (board->get_element(xx + 2, yy - 2) == white) && (board->get_element(xx + 3, yy - 3) == white)) {
			++f;
		}
		if (f > 1) {
			board->remove_move(op);
			return 35;
		}
	}
	
	// Create 4 in a row
	if (t == black) {
		if ((yy >= 3) && (board->get_element(xx, yy - 1) == black) && (board->get_element(xx, yy - 2) == black) && (board->get_element(xx, yy - 3) == black)) {
			board->remove_move(op);
			return 30;
		}
		if ((yy >= 3) && (xx >= 3) && (board->get_element(xx - 1, yy - 1) == black) && (board->get_element(xx - 2, yy - 2) == black) && (board->get_element(xx - 3, yy - 3) == black)) {
			board->remove_move(op);
			return 30;
		}
		if ((xx >= 3) && (board->get_element(xx - 1, yy) == black) && (board->get_element(xx - 2, yy) == black) && (board->get_element(xx - 3, yy) == black)) {
			board->remove_move(op);
			return 30;
		}
		if ((yy <= 11) && (xx >= 3) && (board->get_element(xx - 1, yy + 1) == black) && (board->get_element(xx - 2, yy + 2) == black) && (board->get_element(xx - 3, yy + 3) == black)) {
			board->remove_move(op);
			return 30;
		}
		if ((yy <= 11) && (board->get_element(xx, yy + 1) == black) && (board->get_element(xx, yy + 2) == black) && (board->get_element(xx, yy + 3) == black)) {
			board->remove_move(op);
			return 30;
		}
		if ((yy <= 11) && (xx <= 11) && (board->get_element(xx + 1, yy + 1) == black) && (board->get_element(xx + 2, yy + 2) == black) && (board->get_element(xx + 3, yy + 3) == black)) {
			board->remove_move(op);
			return 30;
		}
		if ((xx <= 11) && (board->get_element(xx + 1, yy) == black) && (board->get_element(xx + 2, yy) == black) && (board->get_element(xx + 3, yy) == black)) {
			board->remove_move(op);
			return 30;
		}
		if ((yy >= 3) && (xx <= 11) && (board->get_element(xx + 1, yy - 1) == black) && (board->get_element(xx + 2, yy - 2) == black) && (board->get_element(xx + 3, yy - 3) == black)) {
			board->remove_move(op);
			return 30;
		}
	}
	else {
		if ((yy >= 3) && (board->get_element(xx, yy - 1) == white) && (board->get_element(xx, yy - 2) == white) && (board->get_element(xx, yy - 3) == white)) {
			board->remove_move(op);
			return -30;
		}
		if ((yy >= 3) && (xx >= 3) && (board->get_element(xx - 1, yy - 1) == white) && (board->get_element(xx - 2, yy - 2) == white) && (board->get_element(xx - 3, yy - 3) == white)) {
			board->remove_move(op);
			return -30;
		}
		if ((xx >= 3) && (board->get_element(xx - 1, yy) == white) && (board->get_element(xx - 2, yy) == white) && (board->get_element(xx - 3, yy) == white)) {
			board->remove_move(op);
			return -30;
		}
		if ((yy <= 11) && (xx >= 3) && (board->get_element(xx - 1, yy + 1) == white) && (board->get_element(xx - 2, yy + 2) == white) && (board->get_element(xx - 3, yy + 3) == white)) {
			board->remove_move(op);
			return -30;
		}
		if ((yy <= 11) && (board->get_element(xx, yy + 1) == white) && (board->get_element(xx, yy + 2) == white) && (board->get_element(xx, yy + 3) == white)) {
			board->remove_move(op);
			return -30;
		}
		if ((yy <= 11) && (xx <= 11) && (board->get_element(xx + 1, yy + 1) == white) && (board->get_element(xx + 2, yy + 2) == white) && (board->get_element(xx + 3, yy + 3) == white)) {
			board->remove_move(op);
			return -30;
		}
		if ((xx <= 11) && (board->get_element(xx + 1, yy) == white) && (board->get_element(xx + 2, yy) == white) && (board->get_element(xx + 3, yy) == white)) {
			board->remove_move(op);
			return -30;
		}
		if ((yy >= 3) && (xx <= 11) && (board->get_element(xx + 1, yy - 1) == white) && (board->get_element(xx + 2, yy - 2) == white) && (board->get_element(xx + 3, yy - 3) == white)) {
			board->remove_move(op);
			return -30;
		}
	}
	
	// Block 4 in a row
	if (t == white) {
		if ((yy >= 3) && (board->get_element(xx, yy - 1) == black) && (board->get_element(xx, yy - 2) == black) && (board->get_element(xx, yy - 3) == black)) {
			board->remove_move(op);
			return -20;
		}
		if ((yy >= 3) && (xx >= 3) && (board->get_element(xx - 1, yy - 1) == black) && (board->get_element(xx - 2, yy - 2) == black) && (board->get_element(xx - 3, yy - 3) == black)) {
			board->remove_move(op);
			return -20;
		}
		if ((xx >= 3) && (board->get_element(xx - 1, yy) == black) && (board->get_element(xx - 2, yy) == black) && (board->get_element(xx - 3, yy) == black)) {
			board->remove_move(op);
			return -20;
		}
		if ((yy <= 11) && (xx >= 3) && (board->get_element(xx - 1, yy + 1) == black) && (board->get_element(xx - 2, yy + 2) == black) && (board->get_element(xx - 3, yy + 3) == black)) {
			board->remove_move(op);
			return -20;
		}
		if ((yy <= 11) && (board->get_element(xx, yy + 1) == black) && (board->get_element(xx, yy + 2) == black) && (board->get_element(xx, yy + 3) == black)) {
			board->remove_move(op);
			return -20;
		}
		if ((yy <= 11) && (xx <= 11) && (board->get_element(xx + 1, yy + 1) == black) && (board->get_element(xx + 2, yy + 2) == black) && (board->get_element(xx + 3, yy + 3) == black)) {
			board->remove_move(op);
			return -20;
		}
		if ((xx <= 11) && (board->get_element(xx + 1, yy) == black) && (board->get_element(xx + 2, yy) == black) && (board->get_element(xx + 3, yy) == black)) {
			board->remove_move(op);
			return -20;
		}
		if ((yy >= 3) && (xx <= 11) && (board->get_element(xx + 1, yy - 1) == black) && (board->get_element(xx + 2, yy - 2) == black) && (board->get_element(xx + 3, yy - 3) == black)) {
			board->remove_move(op);
			return -20;
		}
	}
	else {
		if ((yy >= 3) && (board->get_element(xx, yy - 1) == white) && (board->get_element(xx, yy - 2) == white) && (board->get_element(xx, yy - 3) == white)) {
			board->remove_move(op);
			return 20;
		}
		if ((yy >= 3) && (xx >= 3) && (board->get_element(xx - 1, yy - 1) == white) && (board->get_element(xx - 2, yy - 2) == white) && (board->get_element(xx - 3, yy - 3) == white)) {
			board->remove_move(op);
			return 20;
		}
		if ((xx >= 3) && (board->get_element(xx - 1, yy) == white) && (board->get_element(xx - 2, yy) == white) && (board->get_element(xx - 3, yy) == white)) {
			board->remove_move(op);
			return 20;
		}
		if ((yy <= 11) && (xx >= 3) && (board->get_element(xx - 1, yy + 1) == white) && (board->get_element(xx - 2, yy + 2) == white) && (board->get_element(xx - 3, yy + 3) == white)) {
			board->remove_move(op);
			return 20;
		}
		if ((yy <= 11) && (board->get_element(xx, yy + 1) == white) && (board->get_element(xx, yy + 2) == white) && (board->get_element(xx, yy + 3) == white)) {
			board->remove_move(op);
			return 20;
		}
		if ((yy <= 11) && (xx <= 11) && (board->get_element(xx + 1, yy + 1) == white) && (board->get_element(xx + 2, yy + 2) == white) && (board->get_element(xx + 3, yy + 3) == white)) {
			board->remove_move(op);
			return 20;
		}
		if ((xx <= 11) && (board->get_element(xx + 1, yy) == white) && (board->get_element(xx + 2, yy) == white) && (board->get_element(xx + 3, yy) == white)) {
			board->remove_move(op);
			return 20;
		}
		if ((yy >= 3) && (xx <= 11) && (board->get_element(xx + 1, yy - 1) == white) && (board->get_element(xx + 2, yy - 2) == white) && (board->get_element(xx + 3, yy - 3) == white)) {
			board->remove_move(op);
			return 20;
		}
	}
	
	// Create blocked 3 on 3
	if (t == black) {
		int f = 0;
		if ((yy >= 3) && (board->get_element(xx, yy - 1) == black) && (board->get_element(xx, yy - 2) == black) && (board->get_element(xx, yy - 3) == white)) {
			++f;
		}
		if ((yy >= 3) && (xx >= 3) && (board->get_element(xx - 1, yy - 1) == black) && (board->get_element(xx - 2, yy - 2) == black) && (board->get_element(xx - 3, yy - 3) == white)) {
			++f;
		}
		if ((xx >= 3) && (board->get_element(xx - 1, yy) == black) && (board->get_element(xx - 2, yy) == black) && (board->get_element(xx - 3, yy) == white)) {
			++f;
		}
		if ((yy <= 11) && (xx >= 3) && (board->get_element(xx - 1, yy + 1) == black) && (board->get_element(xx - 2, yy + 2) == black) && (board->get_element(xx - 3, yy + 3) == white)) {
			++f;
		}
		if ((yy <= 11) && (board->get_element(xx, yy + 1) == black) && (board->get_element(xx, yy + 2) == black) && (board->get_element(xx, yy + 3) == white)) {
			++f;
		}
		if ((yy <= 11) && (xx <= 11) && (board->get_element(xx + 1, yy + 1) == black) && (board->get_element(xx + 2, yy + 2) == black) && (board->get_element(xx + 3, yy + 3) == white)) {
			++f;
		}
		if ((xx <= 11) && (board->get_element(xx + 1, yy) == black) && (board->get_element(xx + 2, yy) == black) && (board->get_element(xx + 3, yy) == white)) {
			++f;
		}
		if ((yy >= 3) && (xx <= 11) && (board->get_element(xx + 1, yy - 1) == black) && (board->get_element(xx + 2, yy - 2) == black) && (board->get_element(xx + 3, yy - 3) == white)) {
			++f;
		}
		if (f > 1) {
			board->remove_move(op);
			return 19;
		}
	}
	else {
		int f = 0;
		if ((yy >= 3) && (board->get_element(xx, yy - 1) == white) && (board->get_element(xx, yy - 2) == white) && (board->get_element(xx, yy - 3) == black)) {
			++f;
		}
		if ((yy >= 3) && (xx >= 3) && (board->get_element(xx - 1, yy - 1) == white) && (board->get_element(xx - 2, yy - 2) == white) && (board->get_element(xx - 3, yy - 3) == black)) {
			++f;
		}
		if ((xx >= 3) && (board->get_element(xx - 1, yy) == white) && (board->get_element(xx - 2, yy) == white) && (board->get_element(xx - 3, yy) == black)) {
			++f;
		}
		if ((yy <= 11) && (xx >= 3) && (board->get_element(xx - 1, yy + 1) == white) && (board->get_element(xx - 2, yy + 2) == white) && (board->get_element(xx - 3, yy + 3) == black)) {
			++f;
		}
		if ((yy <= 11) && (board->get_element(xx, yy + 1) == white) && (board->get_element(xx, yy + 2) == white) && (board->get_element(xx, yy + 3) == black)) {
			++f;
		}
		if ((yy <= 11) && (xx <= 11) && (board->get_element(xx + 1, yy + 1) == white) && (board->get_element(xx + 2, yy + 2) == white) && (board->get_element(xx + 3, yy + 3) == black)) {
			++f;
		}
		if ((xx <= 11) && (board->get_element(xx + 1, yy) == white) && (board->get_element(xx + 2, yy) == white) && (board->get_element(xx + 3, yy) == black)) {
			++f;
		}
		if ((yy >= 3) && (xx <= 11) && (board->get_element(xx + 1, yy - 1) == white) && (board->get_element(xx + 2, yy - 2) == white) && (board->get_element(xx + 3, yy - 3) == black)) {
			++f;
		}
		if (f > 1) {
			board->remove_move(op);
			return -19;
		}
	}
	
	// Block blocked 3 on 3
	if (t == white) {
		int f = 0;
		if ((yy >= 3) && (board->get_element(xx, yy - 1) == black) && (board->get_element(xx, yy - 2) == black) && (board->get_element(xx, yy - 3) == white)) {
			++f;
		}
		if ((yy >= 3) && (xx >= 3) && (board->get_element(xx - 1, yy - 1) == black) && (board->get_element(xx - 2, yy - 2) == black) && (board->get_element(xx - 3, yy - 3) == white)) {
			++f;
		}
		if ((xx >= 3) && (board->get_element(xx - 1, yy) == black) && (board->get_element(xx - 2, yy) == black) && (board->get_element(xx - 3, yy) == white)) {
			++f;
		}
		if ((yy <= 11) && (xx >= 3) && (board->get_element(xx - 1, yy + 1) == black) && (board->get_element(xx - 2, yy + 2) == black) && (board->get_element(xx - 3, yy + 3) == white)) {
			++f;
		}
		if ((yy <= 11) && (board->get_element(xx, yy + 1) == black) && (board->get_element(xx, yy + 2) == black) && (board->get_element(xx, yy + 3) == white)) {
			++f;
		}
		if ((yy <= 11) && (xx <= 11) && (board->get_element(xx + 1, yy + 1) == black) && (board->get_element(xx + 2, yy + 2) == black) && (board->get_element(xx + 3, yy + 3) == white)) {
			++f;
		}
		if ((xx <= 11) && (board->get_element(xx + 1, yy) == black) && (board->get_element(xx + 2, yy) == black) && (board->get_element(xx + 3, yy) == white)) {
			++f;
		}
		if ((yy >= 3) && (xx <= 11) && (board->get_element(xx + 1, yy - 1) == black) && (board->get_element(xx + 2, yy - 2) == black) && (board->get_element(xx + 3, yy - 3) == white)) {
			++f;
		}
		if (f > 1) {
			board->remove_move(op);
			return -17;
		}
	}
	else {
		int f = 0;
		if ((yy >= 3) && (board->get_element(xx, yy - 1) == white) && (board->get_element(xx, yy - 2) == white) && (board->get_element(xx, yy - 3) == black)) {
			++f;
		}
		if ((yy >= 3) && (xx >= 3) && (board->get_element(xx - 1, yy - 1) == white) && (board->get_element(xx - 2, yy - 2) == white) && (board->get_element(xx - 3, yy - 3) == black)) {
			++f;
		}
		if ((xx >= 3) && (board->get_element(xx - 1, yy) == white) && (board->get_element(xx - 2, yy) == white) && (board->get_element(xx - 3, yy) == black)) {
			++f;
		}
		if ((yy <= 11) && (xx >= 3) && (board->get_element(xx - 1, yy + 1) == white) && (board->get_element(xx - 2, yy + 2) == white) && (board->get_element(xx - 3, yy + 3) == black)) {
			++f;
		}
		if ((yy <= 11) && (board->get_element(xx, yy + 1) == white) && (board->get_element(xx, yy + 2) == white) && (board->get_element(xx, yy + 3) == black)) {
			++f;
		}
		if ((yy <= 11) && (xx <= 11) && (board->get_element(xx + 1, yy + 1) == white) && (board->get_element(xx + 2, yy + 2) == white) && (board->get_element(xx + 3, yy + 3) == black)) {
			++f;
		}
		if ((xx <= 11) && (board->get_element(xx + 1, yy) == white) && (board->get_element(xx + 2, yy) == white) && (board->get_element(xx + 3, yy) == black)) {
			++f;
		}
		if ((yy >= 3) && (xx <= 11) && (board->get_element(xx + 1, yy - 1) == white) && (board->get_element(xx + 2, yy - 2) == white) && (board->get_element(xx + 3, yy - 3) == black)) {
			++f;
		}
		if (f > 1) {
			board->remove_move(op);
			return 17;
		}
	}
	
	// Create 3 in a row
	if (t == black) {
		if ((yy >= 2) && (board->get_element(xx, yy - 1) == black) && (board->get_element(xx, yy - 2) == black)) {
			board->remove_move(op);
			return 15;
		}
		if ((yy >= 2) && (xx >= 2) && (board->get_element(xx - 1, yy - 1) == black) && (board->get_element(xx - 2, yy - 2) == black)) {
			board->remove_move(op);
			return 15;
		}
		if ((xx >= 2) && (board->get_element(xx - 1, yy) == black) && (board->get_element(xx - 2, yy) == black)) {
			board->remove_move(op);
			return 15;
		}
		if ((yy <= 12) && (xx >= 2) && (board->get_element(xx - 1, yy + 1) == black) && (board->get_element(xx - 2, yy + 2) == black)) {
			board->remove_move(op);
			return 15;
		}
		if ((yy <= 12) && (board->get_element(xx, yy + 1) == black) && (board->get_element(xx, yy + 2) == black)) {
			board->remove_move(op);
			return 15;
		}
		if ((yy <= 12) && (xx <= 12) && (board->get_element(xx + 1, yy + 1) == black) && (board->get_element(xx + 2, yy + 2) == black)) {
			board->remove_move(op);
			return 15;
		}
		if ((xx <= 12) && (board->get_element(xx + 1, yy) == black) && (board->get_element(xx + 2, yy) == black)) {
			board->remove_move(op);
			return 15;
		}
		if ((yy >= 2) && (xx <= 12) && (board->get_element(xx + 1, yy - 1) == black) && (board->get_element(xx + 2, yy - 2) == black)) {
			board->remove_move(op);
			return 15;
		}
	}
	else {
		if ((yy >= 2) && (board->get_element(xx, yy - 1) == white) && (board->get_element(xx, yy - 2) == white)) {
			board->remove_move(op);
			return -15;
		}
		if ((yy >= 2) && (xx >= 2) && (board->get_element(xx - 1, yy - 1) == white) && (board->get_element(xx - 2, yy - 2) == white)) {
			board->remove_move(op);
			return -15;
		}
		if ((xx >= 2) && (board->get_element(xx - 1, yy) == white) && (board->get_element(xx - 2, yy) == white)) {
			board->remove_move(op);
			return -15;
		}
		if ((yy <= 12) && (xx >= 2) && (board->get_element(xx - 1, yy + 1) == white) && (board->get_element(xx - 2, yy + 2) == white)) {
			board->remove_move(op);
			return -15;
		}
		if ((yy <= 12) && (board->get_element(xx, yy + 1) == white) && (board->get_element(xx, yy + 2) == white) && (board->get_element(xx, yy + 3) == white)) {
			board->remove_move(op);
			return -15;
		}
		if ((yy <= 12) && (xx <= 12) && (board->get_element(xx + 1, yy + 1) == white) && (board->get_element(xx + 2, yy + 2) == white)) {
			board->remove_move(op);
			return -15;
		}
		if ((xx <= 12) && (board->get_element(xx + 1, yy) == white) && (board->get_element(xx + 2, yy) == white)) {
			board->remove_move(op);
			return -15;
		}
		if ((yy >= 2) && (xx <= 12) && (board->get_element(xx + 1, yy - 1) == white) && (board->get_element(xx + 2, yy - 2) == white)) {
			board->remove_move(op);
			return -15;
		}
	}
	
	// Block 3 in a row
	if (t == white) {
		if ((yy >= 2) && (board->get_element(xx, yy - 1) == black) && (board->get_element(xx, yy - 2) == black)) {
			board->remove_move(op);
			return -10;
		}
		if ((yy >= 2) && (xx >= 2) && (board->get_element(xx - 1, yy - 1) == black) && (board->get_element(xx - 2, yy - 2) == black)) {
			board->remove_move(op);
			return -10;
		}
		if ((xx >= 2) && (board->get_element(xx - 1, yy) == black) && (board->get_element(xx - 2, yy) == black)) {
			board->remove_move(op);
			return -10;
		}
		if ((yy <= 12) && (xx >= 2) && (board->get_element(xx - 1, yy + 1) == black) && (board->get_element(xx - 2, yy + 2) == black)) {
			board->remove_move(op);
			return -10;
		}
		if ((yy <= 12) && (board->get_element(xx, yy + 1) == black) && (board->get_element(xx, yy + 2) == black)) {
			board->remove_move(op);
			return -10;
		}
		if ((yy <= 12) && (xx <= 12) && (board->get_element(xx + 1, yy + 1) == black) && (board->get_element(xx + 2, yy + 2) == black)) {
			board->remove_move(op);
			return -10;
		}
		if ((xx <= 12) && (board->get_element(xx + 1, yy) == black) && (board->get_element(xx + 2, yy) == black)) {
			board->remove_move(op);
			return -10;
		}
		if ((yy >= 2) && (xx <= 12) && (board->get_element(xx + 1, yy - 1) == black) && (board->get_element(xx + 2, yy - 2) == black)) {
			board->remove_move(op);
			return -10;
		}
	}
	else {
		if ((yy >= 2) && (board->get_element(xx, yy - 1) == white) && (board->get_element(xx, yy - 2) == white)) {
			board->remove_move(op);
			return 10;
		}
		if ((yy >= 2) && (xx >= 2) && (board->get_element(xx - 1, yy - 1) == white) && (board->get_element(xx - 2, yy - 2) == white)) {
			board->remove_move(op);
			return 10;
		}
		if ((xx >= 2) && (board->get_element(xx - 1, yy) == white) && (board->get_element(xx - 2, yy) == white)) {
			board->remove_move(op);
			return 10;
		}
		if ((yy <= 12) && (xx >= 2) && (board->get_element(xx - 1, yy + 1) == white) && (board->get_element(xx - 2, yy + 2) == white)) {
			board->remove_move(op);
			return 10;
		}
		if ((yy <= 12) && (board->get_element(xx, yy + 1) == white) && (board->get_element(xx, yy + 2) == white) && (board->get_element(xx, yy + 3) == white)) {
			board->remove_move(op);
			return 10;
		}
		if ((yy <= 12) && (xx <= 12) && (board->get_element(xx + 1, yy + 1) == white) && (board->get_element(xx + 2, yy + 2) == white)) {
			board->remove_move(op);
			return 10;
		}
		if ((xx <= 12) && (board->get_element(xx + 1, yy) == white) && (board->get_element(xx + 2, yy) == white)) {
			board->remove_move(op);
			return 10;
		}
		if ((yy >= 2) && (xx <= 12) && (board->get_element(xx + 1, yy - 1) == white) && (board->get_element(xx + 2, yy - 2) == white)) {
			board->remove_move(op);
			return 10;
		}
	}
	
	// Create 2 in a row
	if (t == black) {
		if ((yy >= 1) && (board->get_element(xx, yy - 1) == black)) {
			board->remove_move(op);
			return 5;
		}
		if ((yy >= 1) && (xx >= 1) && (board->get_element(xx - 1, yy - 1) == black)) {
			board->remove_move(op);
			return 5;
		}
		if ((xx >= 1) && (board->get_element(xx - 1, yy) == black)) {
			board->remove_move(op);
			return 5;
		}
		if ((yy <= 13) && (xx >= 1) && (board->get_element(xx - 1, yy + 1) == black)) {
			board->remove_move(op);
			return 5;
		}
		if ((yy <= 13) && (board->get_element(xx, yy + 1) == black)) {
			board->remove_move(op);
			return 5;
		}
		if ((yy <= 13) && (xx <= 13) && (board->get_element(xx + 1, yy + 1) == black)) {
			board->remove_move(op);
			return 5;
		}
		if ((xx <= 13) && (board->get_element(xx + 1, yy) == black)) {
			board->remove_move(op);
			return 5;
		}
		if ((yy >= 1) && (xx <= 13) && (board->get_element(xx + 1, yy - 1) == black)) {
			board->remove_move(op);
			return 5;
		}
	}
	else {
		if ((yy >= 1) && (board->get_element(xx, yy - 1) == white)) {
			board->remove_move(op);
			return -5;
		}
		if ((yy >= 1) && (xx >= 1) && (board->get_element(xx - 1, yy - 1) == white)) {
			board->remove_move(op);
			return -5;
		}
		if ((xx >= 1) && (board->get_element(xx - 1, yy) == white)) {
			board->remove_move(op);
			return -5;
		}
		if ((yy <= 13) && (xx >= 1) && (board->get_element(xx - 1, yy + 1) == white)) {
			board->remove_move(op);
			return -5;
		}
		if ((yy <= 13) && (board->get_element(xx, yy + 1) == white)) {
			board->remove_move(op);
			return -5;
		}
		if ((yy <= 13) && (xx <= 13) && (board->get_element(xx + 1, yy + 1) == white)) {
			board->remove_move(op);
			return -5;
		}
		if ((xx <= 13) && (board->get_element(xx + 1, yy) == white)) {
			board->remove_move(op);
			return -5;
		}
		if ((yy >= 1) && (xx <= 13) && (board->get_element(xx + 1, yy - 1) == white)) {
			board->remove_move(op);
			return -5;
		}
	}
	
	// Block 2 in a row
	if (t == white) {
		if ((yy >= 1) && (board->get_element(xx, yy - 1) == black)) {
			board->remove_move(op);
			return -2;
		}
		if ((yy >= 1) && (xx >= 1) && (board->get_element(xx - 1, yy - 1) == black)) {
			board->remove_move(op);
			return -2;
		}
		if ((xx >= 1) && (board->get_element(xx - 1, yy) == black)) {
			board->remove_move(op);
			return -2;
		}
		if ((yy <= 13) && (xx >= 1) && (board->get_element(xx - 1, yy + 1) == black)) {
			board->remove_move(op);
			return -2;
		}
		if ((yy <= 13) && (board->get_element(xx, yy + 1) == black)) {
			board->remove_move(op);
			return -2;
		}
		if ((yy <= 13) && (xx <= 13) && (board->get_element(xx + 1, yy + 1) == black)) {
			board->remove_move(op);
			return -2;
		}
		if ((xx <= 13) && (board->get_element(xx + 1, yy) == black)) {
			board->remove_move(op);
			return -2;
		}
		if ((yy >= 1) && (xx <= 13) && (board->get_element(xx + 1, yy - 1) == black)) {
			board->remove_move(op);
			return -2;
		}
	}
	else {
		if ((yy >= 1) && (board->get_element(xx, yy - 1) == white)) {
			board->remove_move(op);
			return 2;
		}
		if ((yy >= 1) && (xx >= 1) && (board->get_element(xx - 1, yy - 1) == white)) {
			board->remove_move(op);
			return 2;
		}
		if ((xx >= 1) && (board->get_element(xx - 1, yy) == white)) {
			board->remove_move(op);
			return 2;
		}
		if ((yy <= 13) && (xx >= 1) && (board->get_element(xx - 1, yy + 1) == white)) {
			board->remove_move(op);
			return 2;
		}
		if ((yy <= 13) && (board->get_element(xx, yy + 1) == white)) {
			board->remove_move(op);
			return 2;
		}
		if ((yy <= 13) && (xx <= 13) && (board->get_element(xx + 1, yy + 1) == white)) {
			board->remove_move(op);
			return 2;
		}
		if ((xx <= 13) && (board->get_element(xx + 1, yy) == white)) {
			board->remove_move(op);
			return 2;
		}
		if ((yy >= 1) && (xx <= 13) && (board->get_element(xx + 1, yy - 1) == white)) {
			board->remove_move(op);
			return 2;
		}
	}
	
	// Other move
	if (t == black) {
		board->remove_move(op);
		return 1;
	}
	else {
		board->remove_move(op);
		return -1;
	}
}

Operator* Node::get_op() {
	return op;
}

void Node::set_value(int s) {
	value = s;
}

int Node::get_value() {
	return value;
}

Operator* Node::get_child() {
	Tile t = get_op()->get_tile();
	Operator* p;
	int val;
	if (t == black) {
		val = numeric_limits<int>::max();
		for (int i = 1; i <= 15; ++i) {
			for (int j = 1; j <= 15; ++j) {
				Node* n = new Node(board, i, j, white, height - 1, alpha, beta);
				if (board->is_legal(n->get_op())) {
					board->make_move(n->get_op());
					int e = n->minmax();
					if (p == NULL) {
						p = n->get_op();
					}
					else if (e < val) {
						p = n->get_op();
						val = e;
					}
					else {
					}
					board->remove_move(n->get_op());
				}
			}
		}
	}
	else {
		val = numeric_limits<int>::min();
		for (int i = 1; i <= 15; ++i) {
			for (int j = 1; j <= 15; ++j) {
				Node* n = new Node(board, i, j, white, height - 1, alpha, beta);
				if (board->is_legal(n->get_op())) {
					board->make_move(n->get_op());
					int e = n->minmax();
					if (p == NULL) {
						p = n->get_op();
					}
					else if (e > val) {
						p = n->get_op();
						val = e;
					}
					else {
					}
					board->remove_move(n->get_op());
				}
			}
		}
	}
	return p;
}

Tree::Tree(Gamestate* g, int x, int y, Tile t, int h) {
	board = g;
	root = new Node(g, x, y, t, h, numeric_limits<int>::min(), numeric_limits<int>::max());
}

Operator* Tree::best_move() {
	// int v = root->minmax();
	// cerr << "v == " << v << '\n';
	// cerr << root->get_child(v)->get_coordinate().first << ',' << root->get_child(v)->get_coordinate().second << '\n';
	return root->get_child();
}