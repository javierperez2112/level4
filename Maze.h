/**
 *
 */

#include <vector>
#include "API.h"

struct Square
{
    int x, y;
};

enum Direction
{
    UP,
    RIGHT,
    DOWN,
    LEFT
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
    int width;
    int height;
};

Maze initMaze();
void updateDistances(Maze &maze);