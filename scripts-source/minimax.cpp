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
MiniMax::ValidMoves MiniMax::get_valid_moves(Board& a_board) {

    ValidMoves valid_moves;
    valid_moves.amount = 0;

    for(uint8_t x = 0; x < width; x++) {
        if(!a_board.is_column_full(x)) {
            valid_moves.positions[valid_moves.amount] = x;
            valid_moves.amount++;
        }
    }

    return valid_moves;
}

int32_t MiniMax::minimax(Board a_board, uint32_t depth, bool maximizing) {

    //this is a leaf node, so return the score of this board
    if(depth == 0) {
        return board_score(a_board);
    }

    //what do we want to do otherwise?
    switch(is_terminal_node(a_board)) {

        //the AI has gotten a connect four
        case TerminalNodeState::AIWin: {
            return MAX_SCORE;
        }

        //the player has gotten a connect four
        case TerminalNodeState::PlayerWin: {
            return MIN_SCORE;
        }

        //game over.. (draw..?) there are no valid moves left
        case TerminalNodeState::NoValidMoves: {
            return 0;
        }

        //the game continues!
        case TerminalNodeState::NotTerminal: {

            //gather the valid moves
            ValidMoves valid_moves = get_valid_moves(a_board);

            //try to get the highest score possible
            if(maximizing) {

                int32_t value = MIN_SCORE;
                
                //for every column, run minimax on a board copy
                for(uint8_t i = 0; i < valid_moves.amount; i++) {
                    uint8_t column = valid_moves.positions[i];
                    Board board_copy = a_board;
                    board_copy.place_token(column, TokenType::Red);
                    value = std::max(value, minimax(board_copy, depth - 1, false));
                }
                return value;

            } else { //try to get the lowest score possible

                int32_t value = MAX_SCORE;

                for(uint8_t i = 0; i < valid_moves.amount; i++) {
                    uint8_t column = valid_moves.positions[i];
                    Board board_copy = a_board;
                    board_copy.place_token(column, TokenType::Yellow);
                    value = std::min(value, minimax(board_copy, depth - 1, true));
                }

                return value;
            }
        }
    }
}

int32_t MiniMax::board_score(Board& a_board) {
    return 100;
}

MiniMax::TerminalNodeState MiniMax::is_terminal_node(Board& a_board) {
    TokenType victor = a_board.check_victory(nullptr);
    ValidMoves valid_moves = get_valid_moves(a_board);

    switch(victor) {
        case TokenType::Red: { return TerminalNodeState::AIWin;}
        case TokenType::Yellow: { return TerminalNodeState::PlayerWin;}
        case TokenType::Empty: {
            if(valid_moves.amount == 0) {
                return TerminalNodeState::NoValidMoves;
            } else {
                return TerminalNodeState::NotTerminal;
            }
        }
    }
}