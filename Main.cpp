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
    updateDistances(maze);
    while(true)
        makeMove(maze, {0,1});
}
