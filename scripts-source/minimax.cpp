#include "minimax.h"
#include "board.h"

MiniMax::MiniMax(Board& a_board, uint8_t a_width, uint8_t a_height) {
    board = a_board;
    width = a_width;
    height = a_height;
}

uint8_t MiniMax::get_valid_move() {

    //now we choose one randomly for now
    uint8_t index = rand() % width;
    while(board.is_row_full(index)) {
        index = rand() % width;
    }

    return index;
}

void MiniMax::run(uint32_t depth) {

}