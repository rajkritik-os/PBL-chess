#include "board.h"
#include "utils.h" // Make sure you have utils.cpp for keep_alive()!

using namespace chess;

int main()
{
    board chessboard;
    bool is_draw{false};
    
    chessboard.start_message();
    chessboard.alternate_turn(); // Sets turn to White
    
    while (true)
    {
        // 1. Print the current state of the board
        chessboard.print_board();

        // 2. Check for end game conditions
        if (chessboard.is_checkmate())
        {
            std::string winning_player;
            winning_player = (chessboard.get_turncolour() == 'W') ? "Black" : "White";
            chessboard.end_message_win(winning_player);
            
            if (keep_alive()) {
                main(); // Note: Calling main() inside main() is generally frowned upon in C++, but it will work for a simple game.
            }
            break;
        }
        else if (chessboard.is_stalemate())
        {
            chessboard.end_message_draw();
            
            if (keep_alive()) {
                main();
            }
            break;
        }

        // 3. IF NO WIN/DRAW, MAKE A MOVE AND SWITCH TURNS
        chessboard.make_move();
        chessboard.alternate_turn();
    }
    
    return 0;
}