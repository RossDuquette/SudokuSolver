#include "group.h"

Group::Group() :
    squares()
{
}

void Group::add_square(Square& square)
{
    for (int i = 0; i < NUM_SQUARES_PER_GROUP; i++) {
        if (squares[i] == nullptr) {
            squares[i] = &square;
            break;
        }
    }
}

bool Group::eliminate_solved_vals()
{
    bool updated = false;
    for (int i = 0; i < NUM_SQUARES_PER_GROUP; i++) {
        if (squares[i]->is_solved()) {
            if (remove_val_from_possibilities(squares[i]->get_solved_val())) {
                updated = true;
            }
        }
    }
    return updated;
}

bool Group::set_only_val()
{
    bool updated = false;
    for (int val = 0; val < NUM_SQUARES_PER_GROUP; val++) {
        if (set_only_val(val)) {
            updated = true;
            remove_val_from_possibilities(val);
        }
    }
    return updated;
}

bool Group::set_only_val(uint8_t val)
{
    Square* square_to_update = nullptr;
    for (int i = 0; i < NUM_SQUARES_PER_GROUP; i++) {
        if (squares[i]->get_solved_val() == val) {
            return false;
        } else if (squares[i]->can_be(val)) {
            if (square_to_update) {
                // Found another square that can also be val.
                square_to_update = nullptr;
                return false;
            }
            square_to_update = squares[i];
        }
    }
    if (square_to_update) {
        square_to_update->set_solved_val(val);
        return true;
    }
    return false;
}

bool Group::check_for_2_duplicates()
{
    bool updated = false;
    for (int i = 0; i < NUM_SQUARES_PER_GROUP - 1; i++) {
        for (int j = i + 1; j < NUM_SQUARES_PER_GROUP; j++) {
            if ((squares[i]->get_num_possibilities() == 2)
                    && (*(squares[i]) == *(squares[j]))) {
                // Found 2 squares that have the same 2 possibilites.
                // This means that all of the other squares in the group
                // cannot have either of these 2 values.
                if (handle_duplicate_squares(i, j)) {
                    updated = true;
                }
            }
        }
    }
    return updated;
}

bool Group::handle_duplicate_squares(int square1, int square2)
{
    bool updated = false;
    for (int val = 0; val < NUM_SQUARES_PER_GROUP; val++) {
        if (squares[square1]->can_be(val)) {
            if (remove_val_excluding_squares(val, square1, square2)) {
                updated = true;
            }
        }
    }
    return updated;
}

bool Group::remove_val_excluding_squares(uint8_t val, int square1, int square2)
{
    bool updated = false;
    for (int i = 0; i < NUM_SQUARES_PER_GROUP; i++) {
        if ((i == square1) || (i == square2)) {
            continue;
        }
        if (squares[i]->remove_val_from_possibilities(val)) {
            remove_val_from_possibilities(squares[i]->get_solved_val());
            updated = true;
        }
    }
    return updated;
}

bool Group::remove_val_from_possibilities(uint8_t val)
{
    bool updated = false;
    for (int i = 0; i < NUM_SQUARES_PER_GROUP; i++) {
        if (squares[i]->remove_val_from_possibilities(val)) {
            remove_val_from_possibilities(squares[i]->get_solved_val());
            updated = true;
        }
    }
    return updated;
}
