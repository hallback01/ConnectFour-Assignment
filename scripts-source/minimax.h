#pragma once
#include "board.h"

class MiniMax {

    private:
        Board board; // <- start board
        uint8_t width;
        uint8_t height;
        bool is_done;
        const int32_t MAX_SCORE = std::numeric_limits<std::int32_t>::max();
        const int32_t MIN_SCORE = std::numeric_limits<std::int32_t>::min();

        struct ValidMoves {
            uint8_t amount;
            uint8_t positions[255];
        };

        struct DangerousConfigurations {
            uint32_t twos;
            uint32_t threes;
        };

        enum TerminalNodeState {
            NoValidMoves,
            AIWin,
            PlayerWin,
            NotTerminal,
        };

        inline ValidMoves get_valid_moves(Board& a_board);
        inline uint8_t get_random_valid_column(Board& a_board);

        //the actual recursive minimax function.
        //it copies the given board and returns the best column
        int32_t minimax(Board a_board, uint32_t depth, bool maximizing, uint8_t* out_column, int32_t alpha, int32_t beta);

        //checks if a board is terminal.
        //the conditions are (in order):
        // 1. did someone win?
        // 2. are there any valid moves?
        // 3. it's not a terminal node
        TerminalNodeState is_terminal_node(Board& a_board);

        //needed by the heuristic to get a score aproximation within a board state
        inline int32_t board_score(Board& a_board);

        //returns a struct containing the amount of dangerous configurations on the board
        //from a specific player
        DangerousConfigurations get_dangerous_configurations(Board& a_board, TokenType who);
        inline int32_t get_threes(TokenType a, TokenType b, TokenType c, TokenType d, TokenType who);
        inline int32_t get_twos(TokenType a, TokenType b, TokenType c, TokenType d, TokenType who);

    public:
        MiniMax(Board& a_board, uint8_t a_width, uint8_t a_height);
        uint8_t get_optimal_move(uint32_t depth);
};