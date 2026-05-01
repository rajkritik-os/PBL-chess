 #include "subpieces.h"
#include "board.h"
#include <algorithm>

using namespace chess;

bool pawn::is_move_allowed(piece *temp[8][8], int irow, int icol, int frow, int fcol)
{
    int flag{0};
    if (this->get_colour() == 'W') {
        if (frow == irow - 1) {
            if ((fcol == icol - 1 && temp[irow-1][icol-1] != nullptr && temp[irow-1][icol-1]->get_colour() == 'B') ||
                (fcol == icol + 1 && temp[irow-1][icol+1] != nullptr && temp[irow-1][icol+1]->get_colour() == 'B') ||
                (fcol == icol && temp[irow-1][icol] == nullptr)) {
                flag = 1;
            }
        }
        else if (frow == irow - 2 && !has_moved()) {
            if (fcol == icol && temp[irow-1][icol] == nullptr && temp[irow-2][icol] == nullptr) {
                flag = 1;
            }
        }
    }
    else {
        if (frow == irow + 1) {
            if ((fcol == icol - 1 && temp[irow+1][icol-1] != nullptr && temp[irow+1][icol-1]->get_colour() == 'W') ||
                (fcol == icol + 1 && temp[irow+1][icol+1] != nullptr && temp[irow+1][icol+1]->get_colour() == 'W') ||
                (fcol == icol && temp[irow+1][icol] == nullptr)) {
                flag = 1;
            }
        }
        else if (frow == irow + 2 && !has_moved()) {
            if (fcol == icol && temp[irow+1][icol] == nullptr && temp[irow+2][icol] == nullptr) {
                flag = 1;
            }
        }
    }
    return flag == 1;
}

bool bishop::is_move_allowed(piece *temp[8][8], int irow, int icol, int frow, int fcol)
{
    if (abs(frow - irow) != abs(fcol - icol)) return false;
    
    int obstacle{0};
    int distance{abs(frow - irow)};
    int row_dir = (frow - irow < 0) ? -1 : 1;
    int col_dir = (fcol - icol < 0) ? -1 : 1;

    for (int n{1}; n < distance; n++) {
        if (temp[irow + n*row_dir][icol + n*col_dir] != nullptr) {
            obstacle++;
        }
    }
    return obstacle == 0;
}

bool rook::is_move_allowed(piece *temp[8][8], int irow, int icol, int frow, int fcol)
{
    if (frow != irow && fcol != icol) return false;

    int obstacle{0};
    if (frow == irow) {
        int distance = abs(fcol - icol);
        int col_dir = (fcol < icol) ? -1 : 1;
        for (int n{1}; n < distance; n++) {
            if (temp[irow][icol + n*col_dir] != nullptr) obstacle++;
        }
    } else {
        int distance = abs(frow - irow);
        int row_dir = (frow < irow) ? -1 : 1;
        for (int n{1}; n < distance; n++) {
            if (temp[irow + n*row_dir][icol] != nullptr) obstacle++;
        }
    }
    return obstacle == 0;
}

bool knight::is_move_allowed(piece* temp[8][8], int irow, int icol, int frow, int fcol)
{
    return (abs(fcol-icol) == 1 && abs(frow-irow) == 2) ||
           (abs(frow-irow) == 1 && abs(fcol-icol) == 2);
}

bool queen::is_move_allowed(piece* temp[8][8], int irow, int icol, int frow, int fcol)
{
    // Queen = rook + bishop combined
    bool straight = (frow == irow || fcol == icol);
    bool diagonal = (abs(frow-irow) == abs(fcol-icol));
    if (!straight && !diagonal) return false;

    int obstacle{0};
    int row_dir = (frow == irow) ? 0 : (frow > irow ? 1 : -1);
    int col_dir = (fcol == icol) ? 0 : (fcol > icol ? 1 : -1);
    int distance = std::max(abs(frow-irow), abs(fcol-icol));

    for (int n{1}; n < distance; n++) {
        if (temp[irow + n*row_dir][icol + n*col_dir] != nullptr) {
            obstacle++;
        }
    }
    return obstacle == 0;
}

bool king::is_move_allowed(piece* temp[8][8], int irow, int icol, int frow, int fcol)
{
    return abs(frow-irow) <= 1 && abs(fcol-icol) <= 1 &&
           !(frow == irow && fcol == icol);
}