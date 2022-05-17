#pragma once
#include "board.h"

class MiniMax {

    private:
        Board board;
        uint8_t width;
        uint8_t height;

    public:
        MiniMax(Board& a_board, uint8_t a_width, uint8_t a_height);
        void run(uint32_t depth);
        uint8_t get_valid_move();
};