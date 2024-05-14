/**
 *
 */

#include <vector>
#include "API.h"

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
    GraphNode **board;
    Square position;
    Direction direction; 
};

Maze initMaze();
void updateDistances(Maze &maze, Square target);

enum Direction
{
    UP,
    RIGHT,
    DOWN,
    LEFT
};