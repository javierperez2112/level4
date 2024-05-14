#include "Mouse.h"

bool makeMove(Maze &maze, Square move)
{
    if (move.x > 1 || move.y > 1 || move.x < -1 || move.y < -1 || std::abs(move.x + move.y) != 1)
    {
        return false;
    }
    Square newPosition = {maze.position.x + move.x, maze.position.y + move.y};
    bool found = false;
    for (Square position : maze.board[newPosition.x][newPosition.y].neighbors)
    {
        if (newPosition.x == position.x && newPosition.y == position.y)
        {
            found = true;
            break;
        }
    }
    if (!found)
        return false;
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
        /*
        if(moveDirection == UP)
        {
            if(maze.direction == RIGHT)
                API::turnLeft();
            else
                API::turnRight();
            continue;
        }
        if(maze.direction == UP)
        {
            if(moveDirection == RIGHT)
                API::turnRight();
            else
                API::turnLeft();
            continue;
        }
        */
        if (moveDirection > maze.direction)
            API::turnRight();
        else if (moveDirection < maze.direction)
            API::turnLeft();
    }
    API::moveForward(1);
    return true;
}

void updateGraph(Maze &maze)
{
}