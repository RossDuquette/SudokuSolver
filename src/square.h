#ifndef SQUARE_H_
#define SQUARE_H_

#include <cstdint>

#define UNSOLVED_VAL 0xFF

class Square {
    public:
        Square();

        void set_solved_val(uint8_t val);
        bool remove_val_from_possibilities(uint8_t val);

        bool can_be(uint8_t val) const;
        uint8_t get_num_possibilities() const;
        bool is_solved() const;
        uint8_t get_solved_val() const;
        bool operator==(const Square& other) const;

    private:
        void set_solved_from_possibilities();

        uint16_t possible_vals;
        uint8_t num_possibilities;
        uint8_t solved_val;
};

#endif
