#include <stdio.h>
#include <stdlib.h>
#include "solver.h"
#include "image.h"


// N is the size of the 2D matrix   N*N
#define N 9

/* Function to read and store an array from a file */
void load_array(char *filename, int grid[N][N])
{
    FILE *fp;
    fp = fopen(filename, "r");
    int i = 0;
    int j = 0;
    char charac;
    while ((charac = fgetc(fp)) != EOF)
    {
        if (charac != ' ')
        {
            if (charac == '\n')
            {
                j = 0;
                i++;
            }
            else if (charac == '.')
            {
                grid[i][j] = 0;
                j++;
            }
            else
            {
                grid[i][j] = charac - '0';
                j++;
            }
        }
    }
    fclose(fp);
}

/* Function to write a 2D array into a file*/
void write_file(int arr[N][N], char *filename)
{
    FILE *fp;
    fp = fopen(filename, "w");
    int i = 0;
    while (i < N)
    {
        int j = 0;
        while (j < N)
        {
            if (j == 2 || j == 5)
            {
                fprintf(fp, "%d ", arr[i][j]);
            }
            else
            {
                fprintf(fp, "%d", arr[i][j]);
            }
            j++;
        }
        fprintf(fp, "\n");
        if (i == 2 || i == 5)
        {
            fprintf(fp, "\n");
        }
        i++;
    }
    fclose(fp);
}

/* Function to print the matrix */
void print(int arr[N][N])
{
    int i = 0;
    while (i < N)
    {
        int j = 0;
        while(j < N)
        {
            if (j == 2 || j == 5)
            {
                printf("%d ", arr[i][j]);
            }
            else
            {
                printf("%d", arr[i][j]);
            }
            j++;
        }
        printf("\n");
        if (i == 2 || i == 5)
        {
            printf("\n");
        }
        i++;
    }
}

// Function to check if an entry is unassigned
int find_empty_cell(int grid[N][N], int *row, int *col)
{
    for (int x = 0; x < 9; x++)
    {
        for (int y = 0; y < 9; y++)
        {
            if (!grid[x][y])
            {
                *row = x;
                *col = y;
                return 1;
            }
        }
    }
    return 0;
}

// Function to check if the sudoku is correct
int valid(int grid[N][N], int row, int col, int num)
{
    int brow = row / 3 * 3;
    int bcol = col / 3 * 3;

    for (int x = 0; x < 9; ++x)
    {
        if (grid[row][x] == num)
        {
            return 0;
        }
        if (grid[x][col] == num)
        {
            return 0;
        }
        if (grid[brow + (x % 3)][bcol + (x / 3)] == num)
        {
            return 0;
        }
    }
    return 1;
}

// Sudoku Solver
int SudokuSolver(int grid[N][N])
{
    int row;
    int col;
    if (!find_empty_cell(grid, &row, &col))
    {
        return 1;
    }

    for (int n = 1; n < 10; n++)
    {
        if (valid(grid, row, col, n))
        {
            grid[row][col] = n;
            if (SudokuSolver(grid))
            {
                return 1;
            }
            grid[row][col] = 0;
        }
    }
    return 0;
}

/* Function that returns a the solved grid */
int **solved_Grid(int grid[N][N])
{
    if (SudokuSolver(grid))
    {
        return grid;
    }
    else
    {
        return NULL;
    }
}

/* Function to get the file which correspnd to the right input */
char *findPath(char *path, int i)
{
    int j = 0;
    while (path[i] != '\0')
    {
        if (path[j] == (char)i)
        {
            return 1;
        }
        i++;
    }
    return 0;
}

