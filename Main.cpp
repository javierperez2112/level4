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

int main(int argc, char *argv[])
{
    log("Running...");
    Maze maze = initMaze();
    updateDistances(maze);
    // return 0;
    do
    {
        updateGraph(maze);
        updateDistances(maze);
        makeMove(maze, leastDistanceMove(maze));
    } while (maze.board[maze.position.x][maze.position.y].distance != 0);
    API::ackReset();
    maze.position = {0, 0};
    maze.direction = UP;
    do
    {
        updateGraph(maze);
        updateDistances(maze);
        makeMove(maze, leastDistanceMove(maze));
    } while (maze.board[maze.position.x][maze.position.y].distance != 0);
    API::ackReset();
    maze.position = {0, 0};
    maze.direction = UP;
    do
    {
        updateGraph(maze);
        updateDistances(maze);
        makeMove(maze, leastDistanceMove(maze));
    } while (maze.board[maze.position.x][maze.position.y].distance != 0);
    API::ackReset();
    maze.position = {0, 0};
    maze.direction = UP;
    do
    {
        updateGraph(maze);
        updateDistances(maze);
        makeMove(maze, leastDistanceMove(maze));
    } while (maze.board[maze.position.x][maze.position.y].distance != 0);
}
