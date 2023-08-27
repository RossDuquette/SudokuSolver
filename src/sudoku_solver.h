#ifndef SUDOKU_SOLVER_H_
#define SUDOKU_SOLVER_H_

#include "group.h"
#include "square.h"

#define NUM_GROUPS_PER_GRID 9
#define NUM_SQUARES_PER_GRID (NUM_SQUARES_PER_GROUP * NUM_GROUPS_PER_GRID)

enum SetType {
    GROUP_TYPE_ROW,
    GROUP_TYPE_COL,
    GROUP_TYPE_BOX,
    NUM_GROUP_TYPES
};

class SudokuSolver {
    public:
        SudokuSolver();

        void load_file(const char* filename);
        void display_output();
        bool solve();

    private:
        void create_row_groups();
        void create_col_groups();
        void create_box_groups();
        Square& get_square(int row, int col);
        int find_box_num(int row, int col);
        bool update_groups();
        bool eliminate_from_solved_in_group(Group& group);
        bool set_only_val(Group& group);

        Square squares[NUM_SQUARES_PER_GRID];
        Group groups[NUM_GROUP_TYPES][NUM_GROUPS_PER_GRID];
};

#endif
