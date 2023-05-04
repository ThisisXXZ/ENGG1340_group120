#include <iostream>
#include <string>
#include <unistd.h>

#include "player.h"
#include "interface.h"

using namespace std;

void new_game(interface& INT) {
    INT.game_interface();
    getch();                // 过场动画? 
    player newPlayer;
    newPlayer.init(INT);
    newPlayer.simulate_first_semester(INT);
}

int main() {

    interface INT;

    INT.initial_config();
    INT.title_interface();
    getch();
    
    INT.main_interface();
    while (true) {
        INT.output_in_main(" Your prompt here: ");
        string op = INT.input_in_main();
        if (op == "4")
                break;
        else if (op == "2") {
            int saveSlot = INT.select_save_file();
            string saveFilename = "save" + to_string(saveSlot) + ".txt";
            if (player.load_game(saveFilename)) {
                INT.game_interface();
            } else {
                INT.output_in_main("Failed to load save file.");
                }
            }

          else if (op == "1") {
            new_game(INT);
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
    
    INT.end_config();

    cout << "\n\nThis part needs further developing...\n";

    return 0;
}
