#include "board.h"
#include <Godot.hpp>
#include <string>
#include <stack>

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
bool Board::is_column_full(uint8_t index) {
    size_t count = tokens[index].size();
    return count == height;
}

//returns true if the entire board is filled with tokens
bool Board::is_board_full() {

    bool is_full = true;
    for(uint8_t x = 0; x < width; x++) {
        if(!is_column_full(x)) {
            is_full = false;
            break;
        }
    }
    return is_full;
}

//returns the amount of tokens in a row
uint8_t Board::get_column_count(uint8_t index) {
    return tokens[index].size();
}

//places a token inside a column if it's not full
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

//returns TokenType::Empty if the four arguments aren't the same.
//otherwise return the tokentype which they all share
TokenType Board::are_four_coordinates_same(TokenType a, TokenType b, TokenType c, TokenType d) {
    TokenType valor = a;
    if(a == valor && b == valor && c == valor && d == valor) {
        return valor;
    }
    return TokenType::Empty;
}

//checks if one of the player's have won.
//returns TokenType::Empty if no one has won.
//returns TokenType::Red if the AI has won.
//returns TokenType::Yellow if the player has won.
TokenType Board::check_victory(VictoryTokenCoordinates& vtc) {

    //horizontal
    for(size_t j = 0; j < height-3; j++) {
        for(size_t i = 0; i < width; i++) {
            TokenType a = check_coordinate(i, j);
            TokenType b = check_coordinate(i, j+1);
            TokenType c = check_coordinate(i, j+2);
            TokenType d = check_coordinate(i, j+3);
            TokenType check = are_four_coordinates_same(a, b, c, d);
            if(check != TokenType::Empty) {
                godot::Godot::print("horizontal win");
                print_board();

                //fill the victory token coordinate struct
                vtc.x1 = i; vtc.y1 = j;
                vtc.x2 = i; vtc.y2 = j+1;
                vtc.x3 = i; vtc.y3 = j+2;
                vtc.x4 = i; vtc.y4 = j+3;

                return check;
            }
        }
    }

    //vertical
    for(size_t i = 0; i < width-3; i++) {
        for(size_t j = 0; j < height; j++) {
            TokenType a = check_coordinate(i, j);
            TokenType b = check_coordinate(i+1, j);
            TokenType c = check_coordinate(i+2, j);
            TokenType d = check_coordinate(i+3, j);
            TokenType check = are_four_coordinates_same(a, b, c, d);
            if(check != TokenType::Empty) {
                godot::Godot::print("vertical win");
                print_board();

                //fill the victory token coordinate struct
                vtc.x1 = i; vtc.y1 = j;
                vtc.x2 = i+1; vtc.y2 = j;
                vtc.x3 = i+2; vtc.y3 = j;
                vtc.x4 = i+3; vtc.y4 = j;

                return check;
            }
        }
    }

    //ascending diagonal
    for(size_t i = 3; i < width; i++) {
        for(size_t j = 0; i < height-3; j++) {
            TokenType a = check_coordinate(i, j);
            TokenType b = check_coordinate(i-1, j+1);
            TokenType c = check_coordinate(i-2, j+2);
            TokenType d = check_coordinate(i-3, j+3);
            TokenType check = are_four_coordinates_same(a, b, c, d);
            if(check != TokenType::Empty) {
                godot::Godot::print("ascending diagonal win");
                print_board();

                //fill the victory token coordinate struct
                vtc.x1 = i; vtc.y1 = j;
                vtc.x2 = i-1; vtc.y2 = j+1;
                vtc.x3 = i-2; vtc.y3 = j+2;
                vtc.x4 = i-3; vtc.y4 = j+3;

                return check;
            }
        }
    }

    //descending diagonal
    for(size_t i = 3; i < width; i++) {
        for(size_t j = 3; j < height; j++) {
            TokenType a = check_coordinate(i, j);
            TokenType b = check_coordinate(i-1, j-1);
            TokenType c = check_coordinate(i-2, j-2);
            TokenType d = check_coordinate(i-3, j-3);
            TokenType check = are_four_coordinates_same(a, b, c, d);
            if(check != TokenType::Empty) {
                godot::Godot::print("descending diagonal win");
                print_board();

                //fill the victory token coordinate struct
                vtc.x1 = i; vtc.y1 = j;
                vtc.x2 = i-1; vtc.y2 = j-1;
                vtc.x3 = i-2; vtc.y3 = j-2;
                vtc.x4 = i-3; vtc.y4 = j-3;

                return check;
            }
        }
    }

    return TokenType::Empty;
}

void Board::print_board() {

    std::stack<std::string> prints;

    std::string print = "";
    for(size_t y = 0; y < height; y++) {
        for(size_t x = 0; x < width; x++) {
            TokenType token = check_coordinate(x, y);

            if(token == TokenType::Empty) {
                print.append("-");
            }
            if(token == TokenType::Red) {
                print.append("X");
            }
            if(token == TokenType::Yellow) {
                print.append("O");
            }
        }
        prints.push(print);
        print = "";
    }

    while(!prints.empty()) {
        godot::Godot::print(prints.top().c_str());
        prints.pop();
    }
}