#pragma once
#include <vector>

enum TokenType {
    Red,
    Yellow,
    Empty,
};

class Board {

    private:
        std::vector<std::vector<TokenType>> tokens; //x, y
        uint8_t height;
        uint8_t width;

    public:
        Board();
        Board(uint8_t a_width, uint8_t a_height);
        bool is_row_full(uint8_t index);
        bool is_board_full();
        uint8_t get_row_count(uint8_t index);
        void place_token(uint8_t index, TokenType token_type);
        TokenType check_coordinate(uint8_t x, uint8_t y);
        TokenType check_victory();
};