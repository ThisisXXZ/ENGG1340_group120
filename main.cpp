#include <iostream>
#include <string>
#include "player.h"

using namespace std;


void delay() 
{
    //延时cout
    clock_t start_time;//, cur_time;
    start_time = clock();//clock()
    for (; (clock() - start_time) < 2 * CLOCKS_PER_SEC;);//延迟2秒
}  


void printTitle() {
    cout << "\
                                  '##::::'##:'##:::'##:'##::::'##:\n\
                                   ##:::: ##: ##::'##:: ##:::: ##:\n\
                                   ##:::: ##: ##:'##::: ##:::: ##:\n\
                                   #########: #####:::: ##:::: ##:\n\
                                   ##.... ##: ##. ##::: ##:::: ##:\n\
                                   ##:::: ##: ##:. ##:: ##:::: ##:\n\
                                   ##:::: ##: ##::. ##:. #######::\n\
                                  ..:::::..::..::::..:::.......:::\n\
              :'######::'########:'##::::'##:'########::'########:'##::: ##:'########:\n\
              '##... ##:... ##..:: ##:::: ##: ##.... ##: ##.....:: ###:: ##:... ##..::\n\
               ##:::..::::: ##:::: ##:::: ##: ##:::: ##: ##::::::: ####: ##:::: ##::::\n\
              . ######::::: ##:::: ##:::: ##: ##:::: ##: ######::: ## ## ##:::: ##::::\n\
              :..... ##:::: ##:::: ##:::: ##: ##:::: ##: ##...:::: ##. ####:::: ##::::\n\
              '##::: ##:::: ##:::: ##:::: ##: ##:::: ##: ##::::::: ##:. ###:::: ##::::\n\
              . ######::::: ##::::. #######:: ########:: ########: ##::. ##:::: ##::::\n\
              :......::::::..::::::.......:::........:::........::..::::..:::::..:::::\n\
    :'######::'####:'##::::'##:'##::::'##:'##::::::::::'###::::'########::'#######::'########::\n\
    '##... ##:. ##:: ###::'###: ##:::: ##: ##:::::::::'## ##:::... ##..::'##.... ##: ##.... ##:\n\
     ##:::..::: ##:: ####'####: ##:::: ##: ##::::::::'##:. ##::::: ##:::: ##:::: ##: ##:::: ##:\n\
    . ######::: ##:: ## ### ##: ##:::: ##: ##:::::::'##:::. ##:::: ##:::: ##:::: ##: ########::\n\
    :..... ##:: ##:: ##. #: ##: ##:::: ##: ##::::::: #########:::: ##:::: ##:::: ##: ##.. ##:::\n\
    '##::: ##:: ##:: ##:.:: ##: ##:::: ##: ##::::::: ##.... ##:::: ##:::: ##:::: ##: ##::. ##::\n\
    . ######::'####: ##:::: ##:. #######:: ########: ##:::: ##:::: ##::::. #######:: ##:::. ##:\n\
    :......:::....::..:::::..:::.......:::........::..:::::..:::::..::::::.......:::..:::::..::\n";
    
    delay();
    cout << "\nWELCOME!\n\n";
    delay();
    cout << "Welcome to the text-based game of university life simulator! In this game, you will play as a freshman starting your journey at the prestigious Hong Kong University (HKU).";
    delay();
    cout << "You are excited to begin this new chapter of your life and to explore all the opportunities that come with university education.";
    delay();
    cout << "As a player, you will navigate through different events and situations that simulate various aspects of university life, such as academics, social activities, and personal relationships.";
    delay();
    cout << "Every decision you make will have consequences, and your ultimate goal is to achieve success while maintaining a balance between your academic and personal priorities.";
    delay();
    cout << "Are you ready to embark on this exciting and unpredictable journey as a freshman at HKU? Let's begin and see where life takes you on campus!";
}

string input() {
    string c;
    cout << "Your prompt here: \n";
    cin >> c;
    return c;
}

int main() {

    printTitle();
    
    while (true) {
        cout << "1. New Game\n2. Load Game\n3. Tutorial\n4. Config\nq. [EXIT]\n";
        string op = input();
        if (op == "1" || op == "2" || op == "3" || op == "4") 
                break;
        else if (op == "q") {
            cout << "Are you sure to exit? (Y/N)\n";
            op = input();
            if (op == "Y") 
                return 0;
        } else {
            cout << "Invalid prompt!\n";
        }
    }
    
    player newPlayer;
    newPlayer.init();

    system("pause");

    return 0;
}
