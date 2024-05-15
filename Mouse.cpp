#include "Mouse.h"

static Direction moveDirection(Square &move);

/**
 * @brief Make move if possible.
 * 
 * @param maze The maze.
 * @param move The move to make.
 * @return Move is possible and done.
*/
bool makeMove(Maze &maze, Square move)
{
    Square newPosition = {maze.position.x + move.x, maze.position.y + move.y};
    bool found = false;
    auto neighbors = maze.board[maze.position.x][maze.position.y].neighbors;
    for (Square position : neighbors)
    {
        if (newPosition.x == position.x && newPosition.y == position.y)
        {
            found = true;
            break;
        }
    }
    if (!found)
    {
        return false;
    }
    Direction moveDir = moveDirection(move);
    while (maze.direction != moveDir)
    {
        API::turnRight();
    }
    API::moveForward();
    maze.position = newPosition;
    return true;
}

/**
 * @brief Update graph edges based on walls around mouse.
 * 
 * @param maze The maze.
*/
void updateGraph(Maze &maze)
{
    auto currentNode = maze.board[maze.position.x][maze.position.y];
    bool fWall = API::wallFront();
    bool rWall = API::wallRight();
    bool lWall = API::wallLeft();
    std::vector<Square>::iterator iter;
    for (iter = currentNode.neighbors.begin(); iter != currentNode.neighbors.end(); iter++)
    {
        Square move = {iter->x - maze.position.x, iter->y - maze.position.y};
        Direction moveDir = moveDirection(move);
        /**
         * @todo Eliminate invalid connections.
        */
    }
}

/**
 * @brief Determine the direction of a move.
 * 
 * @param move The move.
 * @return The direction of the move.
*/
static Direction moveDirection(Square &move)
{
    if (move.y == 1)
        return UP;
    else if (move.y == -1)
        return DOWN;
    else if (move.x == 1)
        return RIGHT;
    else
        return LEFT;
}