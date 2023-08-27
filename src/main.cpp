#include <iostream>

#include "sudoku_solver.h"

static void print_help()
{
    std::cout << "Must pass in file name as argument\n";
}

int main(int argc, char* argv[])
{
    if (argc == 2) {
        SudokuSolver solver;
        solver.load_file(argv[1]);
        solver.solve();
        solver.display_output();
    } else {
        print_help();
    }
    return 0;
}
