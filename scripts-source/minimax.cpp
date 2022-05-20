#include "minimax.h"
#include "board.h"

MiniMax::MiniMax(Board& a_board, uint8_t a_width, uint8_t a_height) {
    board = a_board;
    width = a_width;
    height = a_height;
    is_done = false;
}

//runs minimax and tries to get the most optimal column which it then returns
uint8_t MiniMax::get_optimal_move(uint32_t depth) {
    uint8_t column = 255;
    int32_t score = minimax(board, depth, true, &column);
    return column;
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

//got help from https://medium.com/analytics-vidhya/artificial-intelligence-at-play-connect-four-minimax-algorithm-explained-3b5fc32e4a4f
//this website has a really good pseudocode snippet! And explains a lot of how this AI works!
int32_t MiniMax::minimax(Board a_board, uint32_t depth, bool maximizing, uint8_t* out_column) {

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
                    int32_t new_value = minimax(board_copy, depth - 1, false, nullptr); //we don't need to pass a column pointer here
                    if(new_value > value) {
                        value = new_value;
                        if(out_column) {*out_column = column;}
                    }
                }
                return value;

            } else { //try to get the lowest score possible

                int32_t value = MAX_SCORE;

                for(uint8_t i = 0; i < valid_moves.amount; i++) {
                    uint8_t column = valid_moves.positions[i];
                    Board board_copy = a_board;
                    board_copy.place_token(column, TokenType::Yellow);
                    int32_t new_value = minimax(board_copy, depth - 1, true, nullptr); //we don't need to pass a column pointer here
                    if(new_value < value) {
                        value = new_value;
                        if(out_column) {*out_column = column;}
                    }
                }
                return value;
            }
        }
    }
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

//got the heuristic from this website https://www.madjakul.com/en/posts/minimax_connect4/#checking-for-connected-3-and-connected-2
int32_t MiniMax::board_score(Board& a_board) {
    DangerousConfigurations player_configs = get_dangerous_configurations(a_board, TokenType::Yellow);
    DangerousConfigurations ai_configs = get_dangerous_configurations(a_board, TokenType::Red);

    if(player_configs.fours) {
        return MIN_SCORE;
    } else if(ai_configs.fours) {
        return MAX_SCORE;
    } else {
        int32_t score = (3 * ai_configs.threes + ai_configs.twos) - (3 * player_configs.threes + player_configs.twos);
        return score;
    }
}

MiniMax::DangerousConfigurations MiniMax::get_dangerous_configurations(Board& a_board, TokenType who) {

    DangerousConfigurations dangerous_configs = {0, 0, 0};

    //horizontal
    for(size_t j = 0; j < height-3; j++) {
        for(size_t i = 0; i < width; i++) {
            TokenType a = a_board.check_coordinate(i, j);
            TokenType b = a_board.check_coordinate(i, j+1);
            TokenType c = a_board.check_coordinate(i, j+2);
            TokenType d = a_board.check_coordinate(i, j+3);
            dangerous_configs.fours += get_fours(a, b, c, d, who); if(dangerous_configs.fours != 0) {return dangerous_configs;}
            dangerous_configs.threes += get_threes(a, b, c, d, who);
            dangerous_configs.twos += get_twos(a, b, c, d, who);
        }
    }

    //vertical
    for(size_t i = 0; i < width-3; i++) {
        for(size_t j = 0; j < height; j++) {
            TokenType a = a_board.check_coordinate(i, j);
            TokenType b = a_board.check_coordinate(i+1, j);
            TokenType c = a_board.check_coordinate(i+2, j);
            TokenType d = a_board.check_coordinate(i+3, j);
            dangerous_configs.fours += get_fours(a, b, c, d, who); if(dangerous_configs.fours != 0) {return dangerous_configs;}
            dangerous_configs.threes += get_threes(a, b, c, d, who);
            dangerous_configs.twos += get_twos(a, b, c, d, who);
        }
    }

    //ascending diagonal
    for(size_t i = 3; i < width; i++) {
        for(size_t j = 0; i < height-3; j++) {
            TokenType a = a_board.check_coordinate(i, j);
            TokenType b = a_board.check_coordinate(i-1, j+1);
            TokenType c = a_board.check_coordinate(i-2, j+2);
            TokenType d = a_board.check_coordinate(i-3, j+3);
            dangerous_configs.fours += get_fours(a, b, c, d, who); if(dangerous_configs.fours != 0) {return dangerous_configs;}
            dangerous_configs.threes += get_threes(a, b, c, d, who);
            dangerous_configs.twos += get_twos(a, b, c, d, who);
        }
    }

    //descending diagonal
    for(size_t i = 3; i < width; i++) {
        for(size_t j = 3; j < height; j++) {
            TokenType a = a_board.check_coordinate(i, j);
            TokenType b = a_board.check_coordinate(i-1, j-1);
            TokenType c = a_board.check_coordinate(i-2, j-2);
            TokenType d = a_board.check_coordinate(i-3, j-3);
            dangerous_configs.fours += get_fours(a, b, c, d, who); if(dangerous_configs.fours != 0) {return dangerous_configs;}
            dangerous_configs.threes += get_threes(a, b, c, d, who);
            dangerous_configs.twos += get_twos(a, b, c, d, who);
        }
    }

    return dangerous_configs;
}

int32_t MiniMax::get_fours(TokenType a, TokenType b, TokenType c, TokenType d, TokenType who) {
    int32_t fours = 0;
    if(a == who) {fours++;}
    if(b == who) {fours++;}
    if(c == who) {fours++;}
    if(d == who) {fours++;}
    if(fours == 4) {
        return 1;
    } else {
        return 0;
    }
}

int32_t MiniMax::get_threes(TokenType a, TokenType b, TokenType c, TokenType d, TokenType who) {

    int32_t threes = 0;
    int32_t blanks = 0;
    if(a == who) {threes++;} else if(a == TokenType::Empty) {blanks++;}
    if(b == who) {threes++;} else if(b == TokenType::Empty) {blanks++;}
    if(c == who) {threes++;} else if(c == TokenType::Empty) {blanks++;}
    if(d == who) {threes++;} else if(d == TokenType::Empty) {blanks++;}

    if(threes == 3 && blanks == 1) {
        return 1;
    } else {
        return 0;
    }
}

int32_t MiniMax::get_twos(TokenType a, TokenType b, TokenType c, TokenType d, TokenType who) {

    int32_t twos = 0;
    int32_t blanks = 0;
    if(a == who) {twos++;} else if(a == TokenType::Empty) {blanks++;}
    if(b == who) {twos++;} else if(b == TokenType::Empty) {blanks++;}
    if(c == who) {twos++;} else if(c == TokenType::Empty) {blanks++;}
    if(d == who) {twos++;} else if(d == TokenType::Empty) {blanks++;}

    if(twos == 2 && blanks == 2) {
        return 1;
    } else {
        return 0;
    }
}