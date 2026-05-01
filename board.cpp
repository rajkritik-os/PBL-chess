#include "board.h"
#include <algorithm>
#include <iostream>
#include <map>

using namespace chess;
using namespace std;

// constructor allocates starting pieces on the board
board::board()
{
    wking_row = 7;
    wking_col = 4;
    bking_row = 0;
    bking_row = 4;

    // allocate pawns
    for (int n = 0; n < 8; n++)
    {
        position[1][n] = new pawn{'B'};
        position[6][n] = new pawn{'W'};
    }

    // allocate black pieces
    position[0][0] = new rook{'B'};
    position[0][1] = new knight{'B'};
    position[0][2] = new bishop{'B'};
    position[0][3] = new queen{'B'};
    position[0][4] = new king{'B'};
    position[0][5] = new bishop{'B'};
    position[0][6] = new knight{'B'};
    position[0][7] = new rook{'B'};

    // alocate white pieces
    position[0][0] = new rook{'W'};
    position[0][1] = new knight{'W'};
    position[0][2] = new bishop{'W'};
    position[0][3] = new queen{'W'};
    position[0][4] = new king{'W'};
    position[0][5] = new bishop{'W'};
    position[0][6] = new knight{'W'};
    position[0][7] = new rook{'W'};
}

board::~board()
{
    for (int i = 0; i < 8; i++)
    {
        for (int j = 0; j < 8; j++)
        {
            delete[] position[i][j];
        }
    }
}

void board::print_board()
{
    // create file square units
    cout << '\n'
         << endl;
    string files_square[8];
    for (int n = 0; n < 8; n++)
    {
        files_square[n] = " ";
        files_square[n].push_back(files[n]);
        files_square[n].push_back(' ');
    }
    string divide_square{" ---"};

    // print upper files
    cout << " ";
    for (int m = 0; m < 8; m++)
    {
        cout << files_square[m];
    }
    cout << "   \n";

    // print boards square and side ranks
    for (int i = 0; i < 8; i++)
    {
        cout << " ";
        for (int p = 0; p < 8; p++)
        {
            cout << divide_square;
        }
        cout << "  " << '\n';
        cout << ranks[i] << ' ';
        for (int j = 0; j < 8; j++)
        {
            if (position[i][j] == nullptr)
            {
                cout << "|  ";
            }
            else if (position[i][j]->get_colour() == 'W')
            {
                cout << '|' << '[' << position[i][j]->get_id() << ']';
            }
            else if (position[i][j]->get_colour() == 'B')
            {
                cout << '|' << '<' << position[i][j]->get_id() << '>';
            }
        }
        cout << "| " << ranks[i] << '\n';
    }

    // print last line and lower files
    cout << " ";
    for (int l = 0; l < 8; l++)
    {
        cout << divide_square;
    }
    cout << " " << '\n';
    cout << " ";
    for (int k = 0; k < 8; k++)
    {
        cout << files_square[k];
    }
    cout << "  " << endl;
}

char board::get_turncolour()
{
    return turncolour;
}
void board::alternate_turn()
{
    turncolour = (turncolour == 'w') ? 'B' : 'w';
}

void board::start_message()
{
    cout << "\n\t--- Chess Game ---\n";
    cout << "\n* Input coordinates as 'a1' to play *\n";
    cout << "\n\t   Game Stareted!" << endl;
}

void board::end_message_win(string &player)
{
    cout << "\n\t.   " << player << " wins!\n"
         << endl;
}
void ::boardend_message_draw()
{
    cout << "\n     It's a stalemate! Draw !\n"
         << endl;
}

// take in and validates user input coordinates; then checks if move is legal
void board::make_move()
{
    string input;
    int irow, icol, frow, fcol;
    find_kings(position);
    while (true)
    {
        if (turncolour == 'W')
        {
            cout << "\n-White player's turn- []" << endl;
        }
        else
        {
            cout << "\n-Black playes's turn- <>" << endl;
        }
        cout << "\nSelect the piece:\n";
        input_checker(input);
        irow = input_converter(input[1], 1);
        icol = input_converter(input[0], 0);

        cout << "\nSelect a destination:\n";
        input_checker(input);
        frow = input_converter(input[1], 1);
        fcol = input_converter(input[0], 0);

        if (position[irow][icol] != nullptr)
        {
            if (position[irow][icol]->get_colour() == turncolour)
            {
                if (position[frow][fcol]->get_colour() != turncolour) {
                    if (position[irow][icol]->get_id() == 'K') {
                        if (!position[irow][icol]->has_moved() && (fcol == 2 || fcol == 6)) {
                            // try castling
                            if (castling(turncolour, fcol)) {
                                position[frow][fcol]->set_has_moved();
                                break;
                            }
                        }
                    }
                    if (position[irow][icol]->is_move_allowed(position, irow, icol, frow, fcol)) {
                        if (!will_king_check(irow, icol, frow, fcol, turncolour)) {
                            // move piece
                            position[frow][fcol] = position[irow][icol];
                            position[irow][icol] = nullptr;
                            if (position[frow][fcol]->get_id() == 'P') {
                                if (frow == 0 || frow == 7) {
                                    pawn_promotion(frow, fcol);
                                }
                            }
                            position[frow][fcol]->set_has_moved();
                            break;
                        } else {
                            print_board();
                            cerr << "\nInvalid move: King will be in chekc" << endl;
                        }
                    } else {
                        print_board();
                        cerr << "\nInvalid move: piece movement not allowed" << endl;
                    }
                } else {
                    print_board();
                    cerr << "\nInvalid move: cannot move to your own piece" << endl;
                }
            } else {
                print_board();
                cerr << "\nInvalid move: not your piece" << endl;
            }
        } else {
            print_board();
            cerr << "\nInvalid move: there is no piece on that square" << endl;
        }
    }
}

void board :: input_checker(string& input)
{
    while(true) {
        cout<< "Coordinate = ";
        cin >> input;
        if(input.length() != 2) {
            print_board();
            cerr<<"\nError : input must be made of two characters"<< endl;
        } else if(isalpha(input[0]) && isdigit(input[1])) {
            int count1{0}, count2{0};
            for (int n = 0; n < 8; n++)
            {
                if(input[0] == files[n]){
                    count1++;
                }
                if(input[1]-48 == ranks[n]){
                    count2++;
                }
            }
            if(count1+count2 != 2) {
                print_board();
                cerr<<"\nError: there is no square on the board" <<endl;
            } else {
                break;
            }
        } else {
            print_board();
            cerr<<"\nError: please input a valid position on the board" <<endl;
        }
    }
}

// convert (files x rank) user input to board coordinates
int board::input_converter(char& i, int mode)
{
    switch(mode) {
        case 0: {
            char* file_ptr = find(begin(files),end(files), i);
            int col = distance(files, file_ptr);
            return col;
        }
        case 1: {
            int* rank_ptr = find(begin(ranks), end(ranks), i-48);
            int row = distance(ranks, rank_ptr);
            return row;
        }
        default: {
            return 0;
        }
    }
}

// updates king coordinate
void board:: find_kings(piece* temp[8][8])
{
    for( int i{0}; i<8; i++) {
        for( int j{0}; j<8; j++) {
            if(temp[i][j]->get_id() == 'K') {
                if(temp[i][j]->get_colour() == 'W') {
                    wking_row = i;
                    wking_col = j;
                } else {
                    bking_row = i;
                    bking_col = j;
                }
            }
        }
    }
}

// checks if any enemy piece can move (attack) to king of given colour
bool board::is_king_check(piece* temp[8][8], char& king_colour)
{
    find_kings(temp);
    int king_row, king_col;
    king_row = (king_colour == 'W') ? wking_row : bking_row;
    king_col = (king_colour == 'W') ? wking_col : bking_col;
    for(int i{0}; i<8; i++){
        for(int j{0}; j<8; j++){
            if(temp[i][j]!= nullptr) {
                if(temp[i][j]->get_colour() != king_colour) {
                    if(temp[i][j]->is_move_allowed(temp, i, j, king_row, king_col)) {
                        return true;
                    }
                }
            }
        }
    }
    return false;
}

// creates a virtual board, makes a virtual move and checks if king is in check
// in that hypothetical situation

bool board::will_king_check(int irow, int icol, int frow, int fcol, char king_colour)
{
    piece* virtual_board[8][8];
    for(int i{0}; i<8; i++) {
        for(int j{0}; j<8; j++){
            virtual_board[i][j] = position[i][j];
        }
    }
    // make virtual move
    virtual_board[frow][fcol] = virtual_board[irow][icol];
    virtual_board[irow][icol] = nullptr;
    if(is_king_check(virtual_board, king_colour)) {
        return true;
    } else {
        return false;
    }
    // delete virtual board
    for(int i{0}; i<8; i++)
    {
        for(int j{0}; j<8; j++)
        {
            delete[] virtual_board[i][j];
        }
    }
}

// searches all 8 squares arounf the king position and checks which move are legal
bool board::can_king_move(char king_colour)
{
    int king_row, king_col;
    king_row = (king_colour == 'W') ? wking_row : bking_row;
    king_col = (king_colour == 'W') ? wking_col : bking_col;
    // map to store squares around the king
    std::map<int,std::map<int,int>> map;
    std::map<int,std::map<int,int>>::iterator ptr1;
    std::map<int,int>::iterator ptr2;
    for (int n{0}; n < 8; n++) {
        map.insert(std::make_pair(n, std::map<int, int>()));
    }
    // check each square around the king
    map[0].insert(std::make_pair(king_row-1, king_col-1));
    map[1].insert(std::make_pair(king_row-1, king_col));
    map[2].insert(std::make_pair(king_row-1, king_col+1));
    map[3].insert(std::make_pair(king_row, king_col-1));
    map[4].insert(std::make_pair(king_row, king_col+1));
    map[5].insert(std::make_pair(king_row+1, king_col-1));
    map[6].insert(std::make_pair(king_row+1, king_col));
    map[7].insert(std::make_pair(king_row+1, king_col+1));

    int allowed_square{0};
    for (ptr1 = map.begin(); ptr1 != map.end(); ptr1++) {
        for (ptr2 = ptr1->second.begin(); ptr2 != ptr1->second.end(); ptr2++) {
            if (ptr2->first >= 0 && ptr2->first < 8 && ptr2->second >= 0 && ptr2->second < 8) {
                if (position[ptr2->first][ptr2->second]->get_colour() != king_colour) {
                    if (!will_king_check(king_row, king_col, ptr2->first, ptr2->second, king_colour)) {
                        allowed_square++;
                    }
                }
            }
        }
    }
    if (allowed_square != 0) {
        return true;
    } else {
        return false;
    }
}
// checks if any piece other than the king can move
bool board::can_any_move()
{
    int allowed_square{0};
    for(int i{0}; i<8; i++){
        for(int j{0}; j<8; j++) {
            if(position[i][j]->get_colour() == turncolour) {
                if(position[i][j]->get_id() !='K') {
                    for(int x{0}; x<8; x++){
                        for(int y{0}; y<8; y++) {
                            if(position[i][j]->is_move_allowed(position, i,j , x, y)) {
                                allowed_square++;
                            }
                        }
                    }
                }
            }
        }
    }
    if(allowed_square != 0) {
        return true; 
    } else {
        return false;
    }
}
bool board::is_checkmate()
{
    if(is_king_check(position, turncolour) && !can_king_move(turncolour)) {
        return true;
    } else {
        return false;
    }
}
bool board::is_stalemate()
{
    if(!is_king_check(position, turncolour) && !can_king_move(turncolour) &&!can_any_move()) {
        return true;
    } else {
        return false;
    }
}

void board::pawn_promotion(int row, int col)
{
    string input;
    cout<<"\nPlease choose a piece to prmte the pawn to (R, N, B or Q): ";
    while(cin>>input) {
        if(input == "Q") {
            position[row][col] = new queen(turncolour);
            break;
        } else if(input == "N") {
            position[row][col] = new knight{turncolour};
            break;
        } else if(input == "B") {
            position[row][col] = new bishop{turncolour};
            break;
        } else if(input == "R") {
            position[row][col] = new rook{turncolour};
            break;
        } else {
            cerr<<"\n Invalid input : please input either R, B, N or Q";
        }
    }
    cout<<"\n";
}

bool board::castling(char king_colour, int fcol)
{
    int king_row, king_col;
    king_row = (king_colour == 'W') ? wking_row : bking_row;
    king_col = (king_colour == 'W') ? wking_row : bking_col;

    int ok_squares{0};
    if(fcol == 2) {
        if(position[king_row][0]->get_id()== 'R' && !position[king_row][0]->has_moved()) {
            for(int n{0}; n<3; n++) {
                if(position[king_row][king_col-(n+1)] == nullptr && !will_king_check(king_row, king_col, king_row, king_col-n, king_colour)) {
                    ok_squares++;
                }
            }
        }
    }
    else {
        if(position[king_row][7]->get_id() == 'R' && !position[king_row][7]->has_moved()) {
            for(int n{0}; n<3; n++) {
                if(n>0) {
                    if(position[king_row][king_col+n] == nullptr && 
                        !will_king_check(king_row, king_col, king_row, king_col+n, king_colour)) {
                        ok_squares++;
                    }
                } else {
                    if(!will_king_check(king_row, king_col, king_row, king_col+n, king_colour)) {
                        ok_squares++;
                    }
                }
            }
        }
    }
    if (ok_squares == 3) {  
        position[king_row][fcol] = position[king_row][king_col];
        position[king_row][king_col] = nullptr;
        if (fcol == 2) {
            position[king_row][fcol+1] = position[king_row][0];
            position[king_row][0] = nullptr;
        } else {
            position[king_row][fcol-1] = position[king_row][7];
            position[king_row][7] = nullptr;
        }
        return true;
    } else {
        return false;
    }
}

