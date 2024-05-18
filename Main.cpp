/**
 * @brief Run the whole procedure.
 *
 * @authors Ignacio Rojana, Rocco Gastaldi, Javier Pérez
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

/**
 * @brief Take optimistic paths in order to explore the maze.
 *
 * @param maze The maze.
 * @param movelist The moveList to fill with moves performed.
 */
static void explore(Maze &maze, moveList &movelist)
{

    std::vector<Square> centerTarget, cornerTarget;
    centerTarget.push_back({maze.width / 2, maze.height / 2});
    centerTarget.push_back({maze.width / 2 - 1, maze.height / 2});
    centerTarget.push_back({maze.width / 2, maze.height / 2 - 1});
    centerTarget.push_back({maze.width / 2 - 1, maze.height / 2 - 1});
    cornerTarget.push_back({0, 0});
    API::ackReset();
    maze.position = {0, 0};
    maze.direction = UP;
    do
    {
        updateGraph(maze);
        updateDistances(maze, centerTarget);
        Square move = leastDistanceMove(maze);
        makeMove(maze, move, movelist);
    } while (maze.board[maze.position.x][maze.position.y].distance != 0);
    moveList dummy;
    do
    {
        updateGraph(maze);
        updateDistances(maze, cornerTarget);
        Square move = leastDistanceMove(maze);
        makeMove(maze, move, dummy);
    } while (maze.board[maze.position.x][maze.position.y].distance != 0);

    updateDistances(maze, centerTarget);
}

int main(int argc, char *argv[])
{
    log("Running...");
    Maze maze = initMaze();
    moveList movelist;
    moveList dummy; // Used to ignore the moves made while exploring.
    int currentDistance;
    log("First run...");
    explore(maze, dummy);
    log("Second run...");
    explore(maze, dummy);
    log("Third run...");
    explore(maze, dummy);
    log("Fourth run...");
    explore(maze, movelist);
    API::ackReset();
    maze.position = {0, 0};
    maze.direction = UP;
    log("Final run...");
    followMoveList(maze, movelist);
    log("Done!");
    deleteMaze(maze);
}
