/**
 * @bug Program crashes, try example maze 4.
 */

#include <iostream>
#include <string>

#include "Maze.h"
#include "Mouse.h"

using namespace std;

void log(const std::string &text)
{
    std::cerr << text << std::endl;
}

static void explore(Maze &maze)
{

    std::vector<Square> centerTarget, cornerTarget;
    centerTarget.push_back({maze.width / 2, maze.height / 2});
    centerTarget.push_back({maze.width / 2 - 1, maze.height / 2});
    centerTarget.push_back({maze.width / 2, maze.height / 2 - 1});
    centerTarget.push_back({maze.width / 2 - 1, maze.height / 2 - 1});
    cornerTarget.push_back({0, 0});
    do
    {
        updateGraph(maze);
        updateDistances(maze, centerTarget);
        Square move = leastDistanceMove(maze);
        makeMove(maze, move);
    } while (maze.board[maze.position.x][maze.position.y].distance != 0);

    do
    {
        updateGraph(maze);
        updateDistances(maze, cornerTarget);
        Square move = leastDistanceMove(maze);
        makeMove(maze, move);
    } while (maze.board[maze.position.x][maze.position.y].distance != 0);

    updateDistances(maze, centerTarget);
}

int main(int argc, char *argv[])
{
    log("Running...");
    Maze maze = initMaze();
    // return 0;
    explore(maze);
    explore(maze);
    explore(maze);
}
