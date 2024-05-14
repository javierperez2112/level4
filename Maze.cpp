/**
 *  Functions related to solving the maze
 */
#include "API.h"
#include "Maze.h"

#include <iterator>

static void dijkstra(Maze &maze, Square currentSquare);

Maze initMaze()
{
    Maze newMaze;
    // Initialize a maze with all squares connected (no walls).
    newMaze.board = (GraphNode **)malloc(API::mazeWidth() * sizeof(GraphNode *));
    for (int i = 0; i < API::mazeHeight(); i++)
    {
        newMaze.board[i] = (GraphNode *)malloc(API::mazeHeight() * sizeof(GraphNode));
    }
    for (int i = 0; i < API::mazeWidth(); i++)
    {
        for (int j = 0; j < API::mazeHeight(); j++)
        {
            if (i > 0)
                newMaze.board[i][j].neighbors.push_back({i - 1, j});
            if (i < API::mazeWidth() + 1)
                newMaze.board[i][j].neighbors.push_back({i + 1, j});
            if (j > 0)
                newMaze.board[i][j].neighbors.push_back({i, j - 1});
            if (j < API::mazeHeight() + 1)
                newMaze.board[i][j].neighbors.push_back({i, j + 1});
            newMaze.board[i][j].visited = false;
        }
    }
    newMaze.position = {0, 0};
    newMaze.direction = UP;
    return newMaze;
}

void updateDistances(Maze &maze, Square target)
{
    for (int i = 0; i < API::mazeWidth(); i++)
    {
        for (int j = 0; j < API::mazeHeight(); j++)
        {
            maze.board[i][j].distance = 100;
            maze.board[i][j].visited = false;
        }
    }
    maze.board[API::mazeWidth() / 2][API::mazeHeight() / 2].distance = 0;
    dijkstra(maze, {API::mazeWidth() / 2, API::mazeHeight() / 2});
}

static void dijkstra(Maze &maze, Square currentSquare)
{
    auto currentNode = &maze.board[currentSquare.x][currentSquare.y];

    for (Square &visitSquare : currentNode->neighbors)
    {
        auto visitNode = &maze.board[visitSquare.x][visitSquare.y];
        if (visitNode->visited)
            continue;
        visitNode->visited = true;
        visitNode->distance = std::min(currentNode->distance + 1, visitNode->distance);
    }
}