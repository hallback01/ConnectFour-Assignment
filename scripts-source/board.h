#pragma once
#include <vector>

enum TokenType {
    Red,
    Yellow,
    Empty,
};

struct VictoryTokenCoordinates {
    uint8_t x1;
    uint8_t y1;
    uint8_t x2;
    uint8_t y2;
    uint8_t x3;
    uint8_t y3;
    uint8_t x4;
    uint8_t y4;
};

class Board {

    private:
        std::vector<std::vector<TokenType>> tokens; //x, y
        uint8_t height;
        uint8_t width;
        TokenType are_four_coordinates_same(TokenType a, TokenType b, TokenType c, TokenType d);
        void print_board();

    public:
        Board();
        Board(uint8_t a_width, uint8_t a_height);
        bool is_column_full(uint8_t index);
        bool is_board_full();
        uint8_t get_column_count(uint8_t index);
        void place_token(uint8_t index, TokenType token_type);
        TokenType check_coordinate(uint8_t x, uint8_t y);
        TokenType check_victory(VictoryTokenCoordinates& vtc);
};