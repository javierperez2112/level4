#include <iostream>
#include <string>

#include "Maze.h"

void log(const std::string &text)
{
    std::cerr << text << std::endl;
}

int main(int argc, char *argv[])
{
    log("Running...");
    Maze maze = initMaze();
    updateDistances(maze);
}
