#include "utils.h"

using namespace std;

bool keep_alive()
{
    char user_choice;
    cout<< "Game ended. Press 'r' (and Enter) to restart or any other key to quit.\n\n";
    cin>>user_choice;
    if(user_choice == 'r') {
        return true;
    }
    return false;
}