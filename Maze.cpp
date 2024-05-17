/**
 *  Functions related to solving the maze
 *
 * @bug Distances are incorrectly set, try example maze 5.
 * Fixed by making the algorithm iterative.
 */
#include "API.h"
#include "Maze.h"

static void fillPath(Maze &maze);

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
    do
    {
        newMaze.board = (GraphNode **)malloc(newMaze.width * newMaze.height * sizeof(GraphNode *));
    } while (newMaze.board == nullptr);
    for (int i = 0; i < newMaze.width; i++)
    {
        do
        {
            newMaze.board[i] = (GraphNode *)malloc(newMaze.height * sizeof(GraphNode));
        } while (newMaze.board[i] == nullptr);
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

void deleteMaze(Maze &maze)
{
    for (int i = 0; i < maze.width; i++)
    {
        free(maze.board[i]);
    }
    free(maze.board);
}

/**
 * @brief Update distances using Dijkstra's algorithm.
 * @note Dijkstra's algorithm is implemented iteratively.
 *
 * @param maze The maze.
 * @param targetSquares List of squares with distance 0.
 */
void updateDistances(Maze &maze, std::vector<Square> &targetSquares)
{
    // Set all nodes to not visited.
    for (int i = 0; i < maze.width; i++)
    {
        for (int j = 0; j < maze.height; j++)
        {
            maze.board[i][j].visited = false;
        }
    }

    // Dijkstra's algorithm.
    std::queue<Square> moves;
    API::clearAllColor();
    for (Square &targetSquare : targetSquares)
    {
        moves.push(targetSquare);
        maze.board[targetSquare.x][targetSquare.y].visited = true;
        API::setColor(targetSquare.x, targetSquare.y, 'g'); // Use the loop to paint targets.
    }
    int distance = 0;
    while (moves.size() > 0)
    {
        int movesSize = moves.size();
        for (int i = 0; i < movesSize; i++)
        {
            Square &currentSquare = moves.front();
            GraphNode &currentNode = maze.board[currentSquare.x][currentSquare.y];
            currentNode.distance = distance;
            for (Square &visitSquare : currentNode.neighbors)
            {
                GraphNode &visitNode = maze.board[visitSquare.x][visitSquare.y];
                if (!visitNode.visited)
                    moves.push(visitSquare);
                visitNode.visited = true;
            }
            moves.pop();
        }
        distance++;
    }

    // Update distances on screen.
    for (int i = 0; i < maze.width; i++)
    {
        for (int j = 0; j < maze.height; j++)
        {
            if (maze.board[i][j].visited)
            {
                API::setText(i, j, std::to_string(maze.board[i][j].distance));
            }
            else
            {
                API::setText(i, j, "inf");
            }
        }
    }

    // Draw supposed best path.
    Square currentSquare = maze.position;
    while (maze.board[currentSquare.x][currentSquare.y].distance > 0)
    {
        API::setColor(currentSquare.x, currentSquare.y, 'b');
        Square leastMove;
        int leastDistance = 2 * maze.width * maze.height;
        for (Square move : maze.board[currentSquare.x][currentSquare.y].neighbors)
        {
            if (maze.board[move.x][move.y].distance < leastDistance)
            {
                leastDistance = maze.board[move.x][move.y].distance;
                leastMove = move;
            }
        }
        currentSquare.x = leastMove.x;
        currentSquare.y = leastMove.y;
    }
}