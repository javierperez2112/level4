/**
 *  Functions related to solving the maze
 *
 * @bug Distances are incorrectly set, try example maze 5.
 * Fixed by making the algorithm iterative.
 */
#include "API.h"
#include "Maze.h"

#include <iterator>
#include <forward_list>
#include <deque>

static void dijkstra(Maze &maze, Square &currentSquare);

/**
 * @brief Create new maze.
 *
 * @return The new maze.
 */
Maze initMaze()
{
    Maze newMaze;
    newMaze.width = API::mazeWidth();
    newMaze.height = API::mazeHeight();
    // Initialize a maze with all squares connected (no walls).
    newMaze.board = (GraphNode **)malloc(newMaze.width * sizeof(GraphNode *));
    for (int i = 0; i < newMaze.width; i++)
    {
        newMaze.board[i] = (GraphNode *)malloc(newMaze.height * sizeof(GraphNode));
    }
    for (int i = 0; i < newMaze.width; i++)
    {
        for (int j = 0; j < newMaze.height; j++)
        {
            if (i > 0)
                newMaze.board[i][j].neighbors.push_back({i - 1, j});
            if (i < newMaze.width - 1)
                newMaze.board[i][j].neighbors.push_back({i + 1, j});
            if (j > 0)
                newMaze.board[i][j].neighbors.push_back({i, j - 1});
            if (j < newMaze.height - 1)
                newMaze.board[i][j].neighbors.push_back({i, j + 1});
            newMaze.board[i][j].visited = false;
        }
    }
    newMaze.position = {0, 0};
    newMaze.direction = UP;
    for (int i = 0; i < newMaze.width; i++)
    {
        API::setWall(i, 0, 's');
        API::setWall(i, newMaze.height - 1, 'n');
    }
    for (int j = 0; j < newMaze.width; j++)
    {
        API::setWall(0, j, 'w');
        API::setWall(newMaze.width - 1, j, 'e');
    }
    return newMaze;
}

/**
 * @brief Update distances based on existing graph edges.
 *
 * @param maze The maze.
 */
void updateDistances(Maze &maze)
{
    int maxDistance = 2 * maze.width * maze.height;
    for (int i = 0; i < maze.width; i++)
    {
        for (int j = 0; j < maze.height; j++)
        {
            maze.board[i][j].distance = maxDistance;
            maze.board[i][j].visited = false;
        }
    }
    Square targetSquare = {maze.width / 2, maze.height / 2};
    maze.board[targetSquare.x][targetSquare.y].distance = 0;

    dijkstra(maze, targetSquare);

    for (int i = 0; i < maze.width; i++)
    {
        for (int j = 0; j < maze.height; j++)
        {
            API::setText(i, j, std::to_string(maze.board[i][j].distance));
        }
    }
}

/**
 * @brief Internal function implementing A Dijkstra-inspired algorithm to assign distances to nodes.
 * @note It works iteratively, not recursively.
 *
 * @param maze The maze.
 * @param currentSquare The square being visited.
 */
static void dijkstra(Maze &maze, Square &currentSquare)
{
    std::deque<Square> moves;
    moves.push_front(currentSquare);
    int distance = 0;
    while (moves.size() > 0)
    {
        int movesSize = moves.size();
        for (Square &move : moves)
        {
            GraphNode *currentNode = &maze.board[move.x][move.y];
            if (currentNode->visited)
            {
                continue;
            }
            currentNode->visited = true;
            currentNode->distance = std::min(distance, currentNode->distance);
            for (Square &neighbor : currentNode->neighbors)
            {
                moves.push_front(neighbor);
            }
        }
        for (int i = 0; i < movesSize; i++)
        {
            moves.pop_back();
        }
        distance++;
    }
}