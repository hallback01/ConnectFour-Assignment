#pragma once
#include "board.h"

class MiniMax {

    private:
        Board board; // <- start board
        uint8_t width;
        uint8_t height;
        bool is_done;

        struct ValidMoves {
            uint8_t amount;
            uint8_t positions[255];
        };

        ValidMoves get_valid_moves();

    public:
        MiniMax(Board& a_board, uint8_t a_width, uint8_t a_height);
        void run(uint32_t depth);
        uint8_t get_optimal_move();
};