#include "Mouse.h"

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
    Direction moveDirection;
    if (move.y == 1)
        moveDirection = UP;
    else if (move.y == -1)
        moveDirection = DOWN;
    else if (move.x == 1)
        moveDirection = RIGHT;
    else
        moveDirection = LEFT;
    while (maze.direction != moveDirection)
    {
        API::turnRight();
    }
    API::moveForward();
    maze.position = newPosition;
    return true;
}

void updateGraph(Maze &maze)
{
}