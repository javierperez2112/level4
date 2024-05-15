#include <iostream>
#include <string>

#include "Maze.h"
#include "Mouse.h"

void log(const std::string &text)
{
    std::cerr << text << std::endl;
}

int main(int argc, char *argv[])
{
    log("Running...");
    Maze maze = initMaze();
    updateGraph(maze);
    updateDistances(maze);
    makeMove(maze, {0,1});
    makeMove(maze, {0,1});
    makeMove(maze, {1,0});
    makeMove(maze, {-1,0});
    makeMove(maze, {0,-1});
    makeMove(maze, {0,-1});
}
