#include <fstream>
#include <iostream>

#include "sudoku_solver.h"

SudokuSolver::SudokuSolver() :
    squares(),
    groups()
{
    create_row_groups();
    create_col_groups();
    create_box_groups();
}

void SudokuSolver::create_row_groups()
{
    for (int row = 0; row < NUM_GROUPS_PER_GRID; row++) {
        for (int col = 0; col < NUM_GROUPS_PER_GRID; col++) {
            Square& square = get_square(row, col);
            groups[GROUP_TYPE_ROW][row].add_square(square);
        }
    }
}

void SudokuSolver::create_col_groups()
{
    for (int row = 0; row < NUM_GROUPS_PER_GRID; row++) {
        for (int col = 0; col < NUM_GROUPS_PER_GRID; col++) {
            Square& square = get_square(row, col);
            groups[GROUP_TYPE_COL][col].add_square(square);
        }
    }
}

void SudokuSolver::create_box_groups()
{
    for (int row = 0; row < NUM_GROUPS_PER_GRID; row++) {
        for (int col = 0; col < NUM_GROUPS_PER_GRID; col++) {
            int box = find_box_num(row, col);
            Square& square = get_square(row, col);
            groups[GROUP_TYPE_BOX][box].add_square(square);
        }
    }
}

Square& SudokuSolver::get_square(int row, int col)
{
    return squares[row * NUM_SQUARES_PER_GROUP + col];
}

int SudokuSolver::find_box_num(int row, int col)
{
    int box = 0;
    if (row >= 6) {
        box = 6;
    } else if (row >= 3) {
        box = 3;
    }
    if (col >= 6) {
        box += 2;
    } else if (col >= 3) {
        box += 1;
    }
    return box;
}

void SudokuSolver::load_file(const char* filename)
{
    std::ifstream fin;
    fin.open(filename);
    if (fin.is_open()) {
        for (int i = 0; i < NUM_SQUARES_PER_GRID; i++) {
            int num;
            fin >> num;
            if (num != 0) {
                // Subtract 1 to make number indexed from 0.
                squares[i].set_solved_val(num - 1);
            }
        }
        fin.close();
    }
}

void SudokuSolver::display_output()
{
    for (int row = 0; row < NUM_GROUPS_PER_GRID; row++) {
        for (int col = 0; col < NUM_GROUPS_PER_GRID; col++) {
            Square& square = get_square(row, col);
            // Add 1 to make number indexed from 1.
            uint8_t solved_val = square.get_solved_val() + 1;
            std::cout << (int) solved_val << " ";
        }
        std::cout << std::endl;
    }
}

bool SudokuSolver::solve()
{
    bool updated = true;
    while (updated) {
        updated = update_groups();

        if (!updated) {
            // TODO:
            // Stuck, try advanced technique.
            // If all possible X's in group A also belong in group B,
            // remove other possible X's in group B.
        }
    }
    return false;
}

bool SudokuSolver::update_groups()
{
    bool updated = false;
    for (int group_type = 0; group_type < NUM_GROUP_TYPES; group_type++) {
        for (int i = 0; i < NUM_GROUPS_PER_GRID; i++) {
            Group& group = groups[group_type][i];
            // Eliminate possibilities based on solved values in group.
            if (group.eliminate_solved_vals()) {
                updated = true;
            }
            // Sets the value if only one square in group can be it.
            if (group.set_only_val()) {
                updated = true;
            }
            // If 2 squares in the same group have the same 2 possible values,
            // remove those possible values from other squares in the group.
            if (group.check_for_2_duplicates()) {
                updated = true;
            }
        }
    }
    return updated;
}
