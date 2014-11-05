// Esteban Solis 10/19 2:11 
#pragma once

#include "Game.h"
#include "Tree.h"


using namespace std;


class Game_Server {
public:
	Game _e;
	Gamestate _f;
	// Primary engine that simulates the current game being played
	// Current implementation does NOT suppose multi-game without the
	// spawn of a new Game_Server object.
	
	//AI _ai;
	// AI that should be used with the Gamestate _e in 
	// the event that the user plays against AI.

public:
	Game_Server();
	// Default Constructor sets up initial conditions
	
	//void Setup_ai(unsigned int difficulty);
	
	// If AI mode is chosen, this function is called.
	// Initializes _ai as well as set difficulty.
	
// 	void run();
	// this is being controlled by the main for the first sprint in order to communicate with the server and telnet
	
	// Server client interface is handled in here. Server makes a
	// socket, binds socket to port, and then listens for connections
	// made to port. List of file descriptors is kept to manage 
	// multiple connections to the server. Communication between the
	// server and client are managed. Incoming messages are handled 
	// while string representations of the gamestate are sent. 
	// TCP rather than UDP seems to be the best solution.
	// Communication in should look something like the following...
	// reply(parse_cmd(input));
	
	unsigned int parse_cmd(std::string s);
	// Parses command and calls associated function.
	// Returns an int that maps to a reply for reply function.
	// DISPLAY 
	// EXIT
	// RANDOM | EASY | MEDIUM | HARD 
	// 		- Handled with _ai.set_difficulty();
	// UNDO - Handled with _e.undo_move();
	// HUMAN-AI - Handled with setup_ai(x); 
	// AI-AI - Handled by setting up AI and treating other AI as client

	
	int parse_move(std::string move);
	//parse the users move to check validity 
	
	string reply(int i);
	// Given an int, replies with corresponding message
	// as well as gamestate update. 
	
	void exit1();
	

	
};

