#pragma once
#include "board.h"

class MiniMax {

    private:
        Board board; // <- start board
        uint8_t width;
        uint8_t height;
        bool is_done;
        const int32_t MAX_SCORE = 10000000;
        const int32_t MIN_SCORE = -10000000;

        struct ValidMoves {
            uint8_t amount;
            uint8_t positions[255];
        };

        enum TerminalNodeState {
            NoValidMoves,
            AIWin,
            PlayerWin,
            NotTerminal,
        };

        ValidMoves get_valid_moves(Board& a_board);

        //the actual recursive minimax function.
        //it copies the given board and returns the best column
        int32_t minimax(Board a_board, uint32_t depth, bool maximizing, uint8_t* out_column);

        //checks if a board is terminal.
        //the conditions are (in order):
        // 1. did someone win?
        // 2. are there any valid moves?
        // 3. it's not a terminal node
        TerminalNodeState is_terminal_node(Board& a_board);

        //needed by the heuristic to get a score aproximation within a board state
        int32_t board_score(Board& a_board);
        //uint32_t get_dangerous_twos(TokenType player, Board& a_board);
        //uint32_t get_dangerous_threes(TokenType player, Board& a_board);
        //uint32_t get_fours(TokenType player, Board& a_board);

    public:
        MiniMax(Board& a_board, uint8_t a_width, uint8_t a_height);
        uint8_t get_optimal_move(uint32_t depth);
};