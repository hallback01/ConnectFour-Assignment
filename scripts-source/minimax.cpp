#include "minimax.h"
#include "board.h"
#include <cassert>

MiniMax::MiniMax(Board& a_board, uint8_t a_width, uint8_t a_height) {
    board = a_board;
    width = a_width;
    height = a_height;
    is_done = false;
}

//after the minimax has executed, this function returns the index of the most
//optimal column for the AI to choose
uint8_t MiniMax::get_optimal_move() {

    //the run function must have been called before this function.
    //"is_done" is set to true after it is done calculating
    assert(!is_done);

    //now we choose one randomly for now
    uint8_t index = rand() % width;
    while(board.is_column_full(index)) {
        index = rand() % width;
    }

    return index;
}

//executes the minimax at a given depth
void MiniMax::run(uint32_t depth) {

}

//this function checks every column if it's full.
//if not add it to the valid moves.
//lastly return the struct with all the valid moves and the amount of valid moves there was
MiniMax::ValidMoves MiniMax::get_valid_moves() {

    ValidMoves valid_moves;
    valid_moves.amount = 0;

    for(uint8_t x = 0; x < width; x++) {
        if(!board.is_column_full(x)) {
            valid_moves.positions[valid_moves.amount] = x;
            valid_moves.amount++;
        }
    }

    return valid_moves;
}