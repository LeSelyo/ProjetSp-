#ifndef SOLVER
#define SOLVER

#include "../utils/image.h"

// N is define for the size of the 2D matrix
#define N 9

void load_array(char *filename, int grid[N][N]);
void write_file(int arr[N][N], char *filename);
void print(int arr[N][N]);
int find_empty_cell(int puzzle[][N], int *row, int *column);
int valid(int puzzle[][N], int row, int column, int guess);
int SudokuSolver(int puzzle[][N]);
int **solved_Grid(int grid[][N]);
char *findPath(char *path,int i)

#endif