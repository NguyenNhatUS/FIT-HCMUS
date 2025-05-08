#include <iostream>

using namespace std;

const int N = 8;       // N-Queens size
int board[N][N] = {0}; // 8x8 Chessboard
int solutions = 0;     // Count valid solutions

// Function to check if a queen can be placed at board[row][col]
bool isSafe(int row, int col) {
    for (int i = 0; i < row; i++) {
        if (board[i][col] == 1) return false; // Check column

        if (col - (row - i) >= 0 && board[i][col - (row - i)] == 1)
            return false; // Check left diagonal

        if (col + (row - i) < N && board[i][col + (row - i)] == 1)
            return false; // Check right diagonal
    }
    return true;
}

// Backtracking function to place queens
void solveNQueens(int row)
{
    if (row == N)
    { // All queens placed successfully
        solutions++;
        return;
    }
    for (int col = 0; col < N; col++)
    {
        if (isSafe(row, col))
        {
            board[row][col] = 1;   // Place queen
            solveNQueens(row + 1); // Recur for next row
            board[row][col] = 0;   // Backtrack
        }
    }
}

int main()
{
    solveNQueens(0);
    cout << solutions << endl;
    return 0;
}