#include "board.h"
#include<algorithm>
#include<iostream>
#include<map>

using namespace chess;
using namespace std;

// constructor allocates starting pieces on the board
board::board()
{
    int wking_row = 7;
    int wking_col = 4;
    int bking_row = 0;
    int bking_row = 4;

    // allocate pawns
    for(int n = 0; n<8; n++) {
        position[1][n]= new pawn{'B'};
        position[6][n]= new pawn{'W'};
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
    for(int i = 0; i<8; i++)
    {
        for(int j = 0; j<8; j++)
        {
            delete[] position[i][j];
        }
    }
}

void board::print_board()
{
    // create file square units
    cout<< '\n' <<endl;
    string files_square[8];
    for(int n= 0; n<8; n++)
    {
        files_square[n] = " ";
        files_square[n].push_back(files[n]);
        files_square[n].push_back(' ');
    }
    string divide_square{" ---"};

    //print upper files
    cout<<" ";
    for(int m = 0; m<8; m++){
        cout<<files_square[m];
    }
    cout<<"   \n";

    //print boards square and side ranks
    for(int i =0; i<8; i++){
        cout<<" ";
        for(int p = 0; p<8; p++){
            cout<< divide_square;
        }
        cout<<"  "<<'\n';
        cout<<ranks[i]<<' ';
        for(int j =0; j<8; j++) {
            if(position[i][j] == nullptr)
            {
                cout<<"|  ";
            }
            else if(position[i][j]->get_colour() == 'W'){
                cout<<'|'<<'['<<position[i][j]->get_id()<<']';
            }
            else if(position[i][j]->get_colour()== 'B')
            {
                cout<< '|'<<'<'<<position[i][j]->get_id()<<'>';
            }
        }
        cout<<"| "<<ranks[i]<<'\n';
    }

    // print last line and lower files
    cout<<" ";
    for(int l = 0; l<8; l++) {
        cout<<divide_square;
    }
    cout<<" "<<'\n';
    cout<<" ";
    for(int k = 0; k<8; k++)
    {
        cout<<files_square[k];
    }
    cout<<"  "<<endl;
}

void board::get_turncolour()
{
    turncolour;
}
void board::alternate_turn()
{
    turncolour = (turncolour == 'w') ? 'B' : 'w';
}


