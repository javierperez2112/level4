#pragma once
#include "Maze.h"
#include <forward_list>

typedef std::queue<Direction> moveList; // Only uses UP, LEFT, RIGHT. Up means forward.

void updateGraph(Maze &maze);
bool makeMove(Maze &maze, Square move, moveList &movelist);
Square leastDistanceMove(Maze &maze);
void followMoveList(Maze &maze, moveList &movelist);