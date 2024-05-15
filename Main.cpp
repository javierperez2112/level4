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
    while(1)
    {
    updateGraph(maze);
    updateDistances(maze);
    makeMove(maze, leastDistanceMove(maze));
    }
    
}
