// Andrew Nemec
// CSCE 315-502
// Project 2
// Game Implementation

#include "Game.h"

void Game::undo() {
	game.remove_move(previous_moves.top());
	previous_moves.pop();
	game.remove_move(previous_moves.top());
	previous_moves.pop();
}

int Game::make_move(char t, int x, int y) {
	Tile tile;
	if (t == 'w') {
		tile = white;
	}
	else {
		tile = black;
	}
	Operator* op = new Operator(x, y, tile);
	if (game.make_move(op)) {
		previous_moves.push(op);
		if (game.is_victory(op)) {
			return 2;
		}
		return 1;
	}
	else {
		return 0;
	}
}

/* String Game:easy_ai(){ // must scan board completely and if black has 3 in a row either diagnoal horiz or vertical must block and if not 
	vector<vector<Tile> > easy_vector = game.copy_vector();
	{  //black - @ - human
	for(int i = 0; i < easy_vector.size(); i++){
		for(int j = 0; j < easy_vector.size(); j++){
			if(v[i][j] == '@'){
				
				//check horizontal  3
				//check vertical for 3
			}
		}
	}
} */

int Game::random_int() {
	
	srand(time(NULL));
	return rand() % 15 + 1;
}

void Game::print_to_screen() {
	game.print_to_screen();
}