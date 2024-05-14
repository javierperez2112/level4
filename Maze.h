/**
 *
 */

#include <vector>

#define MAZE_SIZE 16

struct Square
{
    int x, y;
};

struct GraphNode
{
    int distance;
    bool visited;
    std::vector<Square> neighbors;
};

struct Maze
{
    GraphNode board[MAZE_SIZE][MAZE_SIZE];
    Square position;
};

Maze initMaze();
void updateDistances(Maze maze, Square target);