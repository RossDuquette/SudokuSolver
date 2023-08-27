#include <cmath>

#include "square.h"

Square::Square() :
    possible_vals(0x1FF),
    num_possibilities(9),
    solved_val(UNSOLVED_VAL)
{
}

void Square::set_solved_val(uint8_t val)
{
    possible_vals = (1 << val);
    num_possibilities = 1;
    solved_val = val;
}

bool Square::remove_val_from_possibilities(uint8_t val)
{
    if (is_solved() || !can_be(val)) {
        // Already solved or already removed,
        // cannot remove from possibilities.
        return false;
    }
    possible_vals &= ~(1 << val);
    num_possibilities--;
    if (num_possibilities == 1) {
        set_solved_from_possibilities();
    }
    return true;
}

void Square::set_solved_from_possibilities()
{
    solved_val = log2(possible_vals);
}

bool Square::can_be(uint8_t val) const
{
    return possible_vals & (1 << val);
}

uint8_t Square::get_num_possibilities() const
{
    return num_possibilities;
}

bool Square::is_solved() const
{
    return num_possibilities == 1;
}

uint8_t Square::get_solved_val() const
{
    if (is_solved()) {
        return solved_val;
    }
    return UNSOLVED_VAL;
}

bool Square::operator==(const Square& other) const
{
    return (num_possibilities == other.num_possibilities)
        && (possible_vals == other.possible_vals);
}
