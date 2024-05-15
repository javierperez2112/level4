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
        maze.direction = (Direction)((maze.direction + RIGHT) % 4);
    }
    API::moveForward();
    maze.position = newPosition;
    return true;
}

/**
 * @brief Update graph edges based on walls around mouse.
 *
 * @param maze The maze.
 * @bug Seems to ignore some nodes, try example maze 5.
 * Bug fixed: modulo operator will maintain sign!
 */
void updateGraph(Maze &maze)
{
    auto &currentNode = maze.board[maze.position.x][maze.position.y];
    std::vector<Square>::iterator iter = currentNode.neighbors.begin();
    while (iter != currentNode.neighbors.end())
    {
        Square move = {iter->x - maze.position.x, iter->y - maze.position.y};
        Direction moveDir = moveDirection(move);
        Direction lookDir = (Direction)((moveDir - maze.direction + 4) % 4);
        bool wallInDirection = false;
        switch (lookDir)
        {
        case UP:
            wallInDirection = API::wallFront();
            break;
        case RIGHT:
            wallInDirection = API::wallRight();
            break;
        case LEFT:
            wallInDirection = API::wallLeft();
            break;
        default:
            wallInDirection = false;
            break;
        }
        if (wallInDirection)
        {
            char directionChar;
            switch (moveDir)
            {
            case UP:
                directionChar = 'n';
                break;
            case DOWN:
                directionChar = 's';
                break;
            case RIGHT:
                directionChar = 'e';
                break;
            case LEFT:
                directionChar = 'w';
                break;
            }
            API::setWall(maze.position.x, maze.position.y, directionChar);
            auto &otherNode = maze.board[iter->x][iter->y];
            std::vector<Square>::iterator otherIter = otherNode.neighbors.begin();
            while(otherIter != otherNode.neighbors.end())   // Look for same connection and erase it.
            {
                if(otherIter->x == maze.position.x && otherIter->y == maze.position.y)
                {
                    otherNode.neighbors.erase(otherIter);
                    break;
                }
                otherIter++;
            }
            iter = currentNode.neighbors.erase(iter);
            continue;
        }
        ++iter;
    }
}

Square leastDistanceMove(Maze &maze)
{
    Square leastMove;
    int leastDistance = 2 * maze.width * maze.height;
    for (Square move : maze.board[maze.position.x][maze.position.y].neighbors)
    {
        if (maze.board[move.x][move.y].distance < leastDistance)
        {
            leastDistance = maze.board[move.x][move.y].distance;
            leastMove = move;
        }
    }
    return {leastMove.x - maze.position.x, leastMove.y - maze.position.y};
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