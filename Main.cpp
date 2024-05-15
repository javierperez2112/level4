#include <iostream>
#include <string>

#include "Maze.h"
#include "Mouse.h"

using namespace std;

void log(const std::string &text)
{
    std::cerr << text << std::endl;
}

int main(int argc, char *argv[])
{
    log("Running...");
    Maze maze = initMaze();
    do
    {
        updateGraph(maze);
        updateDistances(maze);
        makeMove(maze, leastDistanceMove(maze));
    } while (maze.board[maze.position.x][maze.position.y].distance != 0);
}
