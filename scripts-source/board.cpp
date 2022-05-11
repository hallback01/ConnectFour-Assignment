#include "board.h"

//empty board
Board::Board() {width = 0; height = 0;}

//initializes a new board with a certain width and height
Board::Board(uint8_t a_width, uint8_t a_height) {

    width = a_width;
    height = a_height;

    for(uint8_t i = 0; i < width; i++) {
        tokens.push_back(std::vector<TokenType>());
    }
}

//checks if a row is full (x value), returns true if it's full
bool Board::is_row_full(uint8_t index) {
    size_t count = tokens[index].size();
    return count == height;
}

//returns true if the entire board is filled with tokens
bool Board::is_board_full() {

    bool is_full = true;
    for(uint8_t x = 0; x < width; x++) {
        if(!is_row_full(x)) {
            is_full = false;
            break;
        }
    }
    return is_full;
}

//returns the amount of tokens in a row
uint8_t Board::get_row_count(uint8_t index) {
    return tokens[index].size();
}

//places a token inside a row if it's not full
void Board::place_token(uint8_t index, TokenType token_type) {
    tokens[index].push_back(token_type);
}

//returns the token type at a given coordinate. 
//must be inside the boundaries given in the constructor
TokenType Board::check_coordinate(uint8_t x, uint8_t y) {

    if(x >= 0 && x < width) {

        if(y < tokens[x].size()) {
            return tokens[x][y];
        } else {
            return TokenType::Empty;
        }
    } else {
        return TokenType::Empty;
    }
}

//checks if one of the player's have won.
//returns TokenType::Empty if no one has won.
//returns TokenType::Red if the AI has won.
//returns TokenType::Yellow if the player has won.
TokenType Board::check_victory() {
    return TokenType::Empty;
}