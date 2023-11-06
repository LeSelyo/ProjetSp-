#include <err.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "image.h"
#include "solver.h"

int main(int argc, char **argv)
{
    int grid[N][N];
    load_array(argv[1], grid);
    print(grid);

    if (argc != 2)
    {
        errx(1, "Wrong number of arguments.");
    }
    else if (argc == 0)
    {
        errx(1, "Not enough arguments entered.");
    }
    else if (SudokuSolver(grid) == 1)
    {
        char *c = ".result";
        char *ex = argv[1];
        strncat(ex, c, 7);
        write_file(grid, ex);
        print(solved_Grid(grid));
    }
    else
    {
        printf("No solution exists\n");
    }

    return 0;
}