/**
 *  Functions related to solving the maze
 */
#include "API.h"
#include "Maze.h"

#include <iterator>

static void dijkstra(Maze &maze, Square &currentSquare);

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
    return newMaze;
}

void updateDistances(Maze &maze)
{
    for (int i = 0; i < maze.width; i++)
    {
        for (int j = 0; j < maze.height; j++)
        {
            maze.board[i][j].distance = 100;
            maze.board[i][j].visited = false;
        }
    }
    Square targetSquare = {maze.width / 2, maze.height / 2};
    maze.board[targetSquare.x][targetSquare.y].distance = 0;
    maze.board[targetSquare.x - 1][targetSquare.y].distance = 0;
    maze.board[targetSquare.x][targetSquare.y - 1].distance = 0;
    maze.board[targetSquare.x - 1][targetSquare.y - 1].distance = 0;
    dijkstra(maze, targetSquare);
    for (int i = 0; i < maze.width; i++)
    {
        for (int j = 0; j < maze.height; j++)
        {
            API::setText(i, j, std::to_string(maze.board[i][j].distance));
        }
    }
}

static void dijkstra(Maze &maze, Square &currentSquare)
{
    auto currentNode = &maze.board[currentSquare.x][currentSquare.y];
    if (currentNode->visited)
        return;
    currentNode->visited = true;

    for (Square &visitSquare : currentNode->neighbors)
    {
        auto visitNode = &maze.board[visitSquare.x][visitSquare.y];
        if (visitNode->visited)
            continue;
        visitNode->distance = std::min(currentNode->distance + 1, visitNode->distance);
    }
    for (Square &visitSquare : currentNode->neighbors)
        dijkstra(maze, visitSquare);
}