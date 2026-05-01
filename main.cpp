#include "board.h"
#include "utils.h"

using namespace chess;
int main()
{
    board chessboard;
    bool is_draw{false};
    chessboard.start_message();
    chessboard.alternate_turn();
    while (true)
    {
        if (chessboard.is_checkmate())
        {
            chessboard.print_board();
            std::string winning_player;
            winning_player = (chessboard.get_turncolour() == 'W') ? "Black" : "White";
            chessboard.end_message_win(winning_player);
            if (keep_alive()) {
                main();
            };
            break;
             
        }
        else if (chessboard.is_stalemate())
        {
            chessboard.print_board();
            chessboard.end_message_draw();
            if (keep_alive())
            {
                main();
            };
            break;
        }
        chessboard.print_board();
    }
    return 0;
}