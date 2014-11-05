// Esteban Solis 10/19 2:11  
// We are still in need of an AI 

#include "game_server.h"


using namespace std; 


extern bool display = false; // check if called 
extern bool AI_Set = false;
extern bool AI_diff_Set = false;
extern string diff = "";
extern bool ai_minmax = 0;
extern int xxx = 1; // odd black - even white
int prev_move_x;
int prev_move_y;

Game_Server::Game_Server() {
	Game _e;
	Gamestate* _f; // make_move for ai will take care of the AI and follow it 
}

int ctoi(char c) {
	int i = (int) c;
	if (i < 60) {
		return i - 48;
	}
	else {
		return i - 87;
	}
}

int Game_Server::parse_move(string move)
{

	
		
		if (move[1] == '1'|| move[1] == '2' || move[1] == '3' || move[0] == '4' || move[1] == '5' || move[1] == '6'|| move[1] == '7' || move[1] == '8' || move[1] == '9'|| move[1] == 'a' || move[1] == 'b' || move[1] == 'c'|| move[1] == 'd' || move[1] == 'e' || move[1] == 'f')
		{
			if(move[0] == '1'|| move[0] == '2'  || move[0] == '3' || move[0] == '4' || move[0] == '5' || move[0] == '6'|| move[0] == '7' || move[0] == '8' || move[0] == '9'|| move[0] == 'a' || move[0] == 'b' || move[0] == 'c'|| move[0] == 'd' || move[0] == 'e' || move[0] == 'f')
			{
					 // black always starts and humans always black
				if(ai_minmax == 1){ // this black move is for med & hard only
					if(xxx % 2 == 1){	
						while(1){
								//black victory 
								int x = _e.make_move('b', ctoi(move[0]), ctoi(move[1]));
								Operator* _o = new Operator(ctoi(move[0]), ctoi(move[1]), black);
								_f.make_move(_o); // gamestate ai must pass in op for gamestate
								if(x == 0) //illegal
									return 0;
								if(x == 1){ // legal
									xxx++;
									prev_move_x = ctoi(move[0]);
									prev_move_y = ctoi(move[1]);
									return 3;}
								if(x == 2)	// victory
									return 5;
						}
					}

				}
				if(ai_minmax == 0){
					if(xxx % 2 == 1){	 // this black move is for easy only only
						while(1){
								//black victory 
								int x = _e.make_move('b', ctoi(move[0]), ctoi(move[1]));
								if(x == 0) //illegal
									return 0;
								if(x == 1){ // legal
									xxx++;
									return 3;}
								if(x == 2)	// victory
									return 5;
							}
					}
				}	
				//--------------------------------------------------
				if(diff == "easy"){	
						if(xxx % 2 == 0){	
						move[0] = _e.random_int();
						move[1] = _e.random_int();
						while(1){
								// white victory
								int y = _e.make_move('w', move[0], move[1]);
							
								if(y == 0) //illegal
									return 0;
								if(y == 1){ // legal
									xxx++; 
									return 3;}
								if(y == 2)	// victory
									return 4;
							}	
						}
				}
				
				if(diff == "medium"){	
						if(xxx % 2 == 0){
							Tree* _t = new Tree(&_f, prev_move_x, prev_move_y, black , 2);
							Operator* _o = _t -> best_move();
							move[0] = _o->get_coordinate().first;
							move[1] = _o->get_coordinate().second;				
							while(1){
									// white victory
									int y = _e.make_move('w', move[0], move[1]);
									Operator* _o = new Operator(move[0], move[1], white);
									_f.make_move(_o);
									if(y == 0) //illegal
										return 0;
									if(y == 1){ // legal
										xxx++;
										delete _t;
										return 3;}
									if(y == 2)	// victory
										return 4;
										
								}	
						}	
				}
				
				if(diff == "hard"){
						if(xxx % 2 == 0){
							Tree* _t = new Tree(&_f, prev_move_x, prev_move_y, black , 4);
							Operator* _o = _t -> best_move();
							move[0] = _o->get_coordinate().first;
							move[1] = _o->get_coordinate().second;				
							while(1){
									// white victory
									int y = _e.make_move('w', move[0], move[1]);
									Operator* _o = new Operator(move[0], move[1], white);
									_f.make_move(_o);
									if(y == 0) //illegal
										return 0;
									if(y == 1){ // legal
										xxx++;
										delete _t;
										return 3;}
									if(y == 2)	// victory
										return 4;
										
								}	
						}	
				}
			}
			else 
			{	
				return 0; 
			}
		}
		else 
		{
			return 0; 
		}
	
}

unsigned int Game_Server::parse_cmd(string s){
	
	if(s.length() < 3)
		return 0;
	s.erase(s.end()-2, s.end());

	
	if(s == "HUMAN-AI" && !AI_Set) {AI_Set = true; }
	

	else if(s == "EASY" && !AI_diff_Set && AI_Set) {cout << "Easy AI " << endl; AI_diff_Set = true; diff = "easy";}
	else if(s == "MEDIUM" && !AI_diff_Set && AI_Set) {cout << "Medium AI " << endl; AI_diff_Set = true; diff = "medium"; ai_minmax = 1;}
	else if(s == "HARD" && !AI_diff_Set && AI_Set) {cout << "Hard AI " << endl; AI_diff_Set = true; diff = "hard"; ai_minmax = 1; }
	
	else if(s == "DISPLAY" && AI_Set && AI_diff_Set && !display) {display = true; return 3;}
	else if(s == "UNDO" && AI_Set && AI_diff_Set) {_e.undo();}
	else if(s == "EXIT") {exit1();}
	
	
	else if(s.length() == 2 && AI_Set && AI_diff_Set && display){ return parse_move(s);}
	
	else 
	{
		return 0;
	}
	
		return 1;

}

string Game_Server::reply(int i) {
	if( i == 0)
		return "ILLEGAL COMMAND\n";
	if(i == 1)
		return "OK\n";
	if(i== 2)
		return "Enter Move\n";
	if(i == 3) {
		_e.print_to_screen();
		return "Next Turn"; // print board 
	}
	if(i == 4)
		cout << "White Won" << endl;
	if(i == 5)	
		cout << "Black Won" << endl; 
	
	return "\n";
}

void Game_Server::exit1() {
	//exits program 
	cout<<"EXITING..." <<endl;
	exit(EXIT_SUCCESS);
}