# 			MAKEFILE 

CC=g++

all: main

main: main.o game_server.o Game.o Tree.o Gamestate.o Operator.o  
	g++-4.7 -std=c++11 -o main main.cpp game_server.o Game.o Tree.o Gamestate.o Operator.o 
	
Operator.o: Operator.h Operator.cpp
	g++-4.7 -std=c++11 -c Operator.cpp
	
Gamestate.o: Gamestate.h Gamestate.cpp
	g++-4.7 -std=c++11 -c Gamestate.cpp
	
Game.o: Game.h Game.cpp
	g++-4.7 -std=c++11 -c Game.cpp

Tree.o: Tree.h Tree.cpp
	g++-4.7 -std=c++11 -c Tree.cpp
	
game_server.o: game_server.h game_server.cpp
	g++-4.7 -std=c++11 -c game_server.cpp 
	
main.o: main.cpp
	g++-4.7 -std=c++11 -c main.cpp

clean:
	rm *.o main	
	
	