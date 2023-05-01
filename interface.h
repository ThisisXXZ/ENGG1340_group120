#ifndef INTERFACE
#define INTERFACE

#include <ncurses.h>
#include <string>

using namespace std;

class interface {

    int ConRow, ConCol;

    WINDOW* main_upwin;
    WINDOW* main_downwin;                   // for main interface: subscrs for stdscr
    WINDOW* tutscr;                         // for tutorial interface
    WINDOW* gamescr;
    WINDOW* game_upwin;
    WINDOW* game_downwin;
    WINDOW* game_rhtwin;                    // for game interface: subscr for gamescr

public:

    WINDOW* get_rhtwin();
    WINDOW* get_gamewin();

    void color_config();
    void initial_config();
    void end_config();

    void title_interface();

    string input_in_main();
    void output_in_main(string);
    void main_interface();

    void tut_print(WINDOW*, string);
    void tutorial_interface();

    int select_save_file();
    
    void game_interface();
    string input_in_game_str(string prom = "Your prompt here: ");
    int input_in_game_int(string prom = "Your prompt here: ");
    void clearwin_in_game();
    void output_in_game(string s, int col = 7, bool typ = true, 
                        bool udl = false, bool blk = false, 
                        bool bld = false, string des = "%s");
};

#endif
