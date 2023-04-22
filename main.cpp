#include <iostream>
#include <string>
#include <unistd.h>
#include "player.h"
#include "interface.h"

using namespace std;


int main() {

    initscr();

    initial_config();
    title_interface();
    getch();
    
    main_interface();
    while (true) {
        output_in_main(" Your prompt here: ");
        string op = input_in_main();
        if (op == "2" || op == "4")
                break;
        else if (op == "1") {
            output_in_main(" Adapt to Linux in progress... ");
            getch();
        } else if (op == "3") {
            tutorial_interface();
        } else if (op == "q") {
            output_in_main(" Are you sure to exit? (Y/N): ");
            op = input_in_main();
            if (op == "Y") 
                break;
        } else {
            output_in_main(" Invalid prompt! (Press any key to proceed...)");
            getch();
        }
    }
    
//    player newPlayer;
//    newPlayer.init();

//    system("pause");

    endwin();

    cout << "\n\nThis part needs further developing...\n";

    return 0;
}
