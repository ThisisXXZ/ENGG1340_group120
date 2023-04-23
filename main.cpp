#include <iostream>
#include <string>
#include <unistd.h>

#include "player.h"
#include "interface.h"

using namespace std;


int main() {

    interface INT;

    INT.initial_config();
    INT.title_interface();
    getch();
    
    INT.main_interface();
    while (true) {
        INT.output_in_main(" Your prompt here: ");
        string op = INT.input_in_main();
        if (op == "2" || op == "4")
                break;
        else if (op == "1") {
            INT.game_interface();
            getch();
            break;
        } else if (op == "3") {
            INT.tutorial_interface();
        } else if (op == "q") {
            INT.output_in_main(" Are you sure to exit? (Y/N): ");
            op = INT.input_in_main();
            if (op == "Y") 
                break;
        } else {
            INT.output_in_main(" Invalid prompt! (Press any key to proceed...)");
            getch();
        }
    }
    
    player newPlayer;
    newPlayer.init(INT);

//    system("pause");

    INT.end_config();

    cout << "\n\nThis part needs further developing...\n";

    return 0;
}
