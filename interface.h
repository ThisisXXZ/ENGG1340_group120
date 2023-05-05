#ifndef INTERFACE
#define INTERFACE

#include <ncurses.h>
#include <string>

using namespace std;

class interface {

    int ConRow, ConCol;                     // the size of the terminal

    WINDOW* main_upwin;                     // windows of main interface
    WINDOW* main_downwin;                   // for main interface: subscrs for stdscr
    WINDOW* tutscr;                         // windows of tutorial interface
    WINDOW* gamescr;                        // windows of game interface
    WINDOW* game_upwin;
    WINDOW* game_downwin;
    WINDOW* game_rhtwin;                    // for game interface: subscr for gamescr
    WINDOW* savescr;
    WINDOW* save_upwin;
    WINDOW* save_downwin;                   // for save interface
    WINDOW* loadscr;
    WINDOW* load_upwin;
    WINDOW* load_downwin;

public:

    WINDOW* get_rhtwin();                   // getters for right windows in game interface
    WINDOW* get_gamewin();                  // getters for the game interface

    void color_config();                    // initialize the color in ncurses
    void initial_config();                  // initialize the standard screen and get the size of the terminal
    void end_config();                      // delete all the created windows and end the ncurses process

    void title_interface();                 // the interface for title

    string input_in_main();                 // prompt player for input in main interface
    void output_in_main(string);            // output texts in main interface
    void main_interface();                  // create and initialize the main interface

    void tut_print(WINDOW*, string);        // output text in tutorial interface
    void tutorial_interface();              // create and initialize the tutorial interface

    void game_interface();                  // create and initialize the game interface
    string input_in_game_str(string prom = "Your input here: ");  // prompt player for input (in the form of string) in game interface
    int input_in_game_int(string prom = "Your choice here: ");    // prompt player for choice (in the form of int) in game interface
    void clearwin_in_game();                                      // clean all the texts in game interface
    void output_in_game(string s, int col = 7, bool typ = true,   // output texts in game interface: the parameters controls the style/color of the texts
                        bool udl = false, bool blk = false, 
                        bool bld = false, string des = "%s");
    string input_in_save(string prom = "Your command here: ");    // prompt player for command in save interface
    void save_interface(string&);                                 // create and initialize the save interface
    string input_in_load(string prom = "Your command here: ");    // prompt player for command in load interface
    void load_interface(string&);                                 // create and initialize the load interface
};

#endif