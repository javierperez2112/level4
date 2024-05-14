/**
 *
 */

#include "Maze.h"

Maze initMaze()
{
    Maze newMaze;
    // Initialize a maze with all squares connected (no walls).
    for (int i = 0; i < MAZE_SIZE; i++)
    {
        for (int j = 0; j < MAZE_SIZE; j++)
        {
            if (i > 0)
                newMaze.board[i][j].neighbors.push_back({i - 1, j});
            if (i < MAZE_SIZE + 1)
                newMaze.board[i][j].neighbors.push_back({i + 1, j});
            if (j > 0)
                newMaze.board[i][j].neighbors.push_back({i, j - 1});
            if (j < MAZE_SIZE + 1)
                newMaze.board[i][j].neighbors.push_back({i, j + 1});
            newMaze.board[i][j].visited = false;
        }
    }
    newMaze.position = {0, 0};
    return newMaze;
}

void updateDistances(Maze maze, Square target)
{
    
}