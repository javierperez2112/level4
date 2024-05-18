/**
 *
 */

#pragma once

#include <vector>
#include <iterator>
#include <queue>
#include "API.h"

/**
 * @brief Struct used to represent positions or changes in position on the maze.
*/
struct Square
{
    int x;
    int y;
};

/**
 * @brief Used to represent directions as integers.
 * @note Directions can be added to represent consecutive transformations, remember to apply % 4.
*/
enum Direction
{
    UP = 0,
    RIGHT = 1,
    DOWN = 2,
    LEFT = 3
};

/**
 * @brief A node representing a single square on the maze.
 * @note Neighbor nodes are linked via their position using "Square".
*/
struct GraphNode
{
    int distance;
    bool visited;
    std::vector<Square> neighbors;
};

/**
 * @brief A whole maze simulation, including the maze itself and state of the mouse.
*/
struct Maze
{
    GraphNode **board;  // Matrix of nodes, needs to be allocated.
    Square position;    // Current position of the mouse.
    Direction direction;    // Current direction of the mouse.
    int width;
    int height;
};

Maze initMaze();
void updateDistances(Maze &maze, std::vector<Square> &targetSquares);
void deleteMaze(Maze &maze);