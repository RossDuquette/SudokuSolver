#ifndef GROUP_H_
#define GROUP_H_

#include <cstdint>

#include "square.h"

#define NUM_SQUARES_PER_GROUP 9

class Group {
    public:
        Group();

        void add_square(Square& square);
        bool eliminate_solved_vals();
        bool set_only_val();
        bool check_for_2_duplicates();

    private:
        bool set_only_val(uint8_t val);
        bool handle_duplicate_squares(int square1, int square2);
        bool remove_val_excluding_squares(uint8_t val, int square1, int square2);
        bool remove_val_from_possibilities(uint8_t val);

        Square* squares[NUM_SQUARES_PER_GROUP];
};

#endif
