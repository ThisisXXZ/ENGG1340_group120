#include <unistd.h>
#include <string>
#include "interface.h"

using namespace std;

// initialize color module and obtain the size of terminal
// suggested size: 30 * 120

void interface::color_config() { 
    if (has_colors()) {
        start_color();
        init_pair(1, COLOR_CYAN, COLOR_BLACK);        // Cyan: mental text
        init_pair(2, COLOR_GREEN, COLOR_BLACK);       // Green: responsive text
        init_pair(3, COLOR_RED, COLOR_BLACK);         // Red: warning text
        init_pair(4, COLOR_YELLOW, COLOR_BLACK);      // Yellow: interactive text
        init_pair(5, COLOR_MAGENTA, COLOR_BLACK); 
        init_pair(6, COLOR_BLUE, COLOR_BLACK);
        init_pair(7, COLOR_WHITE, COLOR_BLACK);       // White: normal text
    }
}

void interface::initial_config() {
    initscr();
    color_config();
    getmaxyx(stdscr, ConRow, ConCol);
}

void interface::end_config() {
    delwin(game_downwin);
    delwin(game_rhtwin);
    delwin(game_upwin);
    delwin(gamescr);
    delwin(save_upwin);
    delwin(save_downwin);
    delwin(savescr);
    endwin();
}

WINDOW* interface::get_gamewin()   { return gamescr; }
WINDOW* interface::get_rhtwin()    { return game_rhtwin; }

// title interface

void interface::title_interface() {                  // manipulate on standard screen
    const int ys = ConCol / 2 - 46;

    attron(COLOR_PAIR(1));
    mvprintw(2 , ys, "                              '##::::'##:'##:::'##:'##::::'##:                             \n");
    mvprintw(3 , ys, "                               ##:::: ##: ##::'##:: ##:::: ##:                             \n");
    mvprintw(4 , ys, "                               ##:::: ##: ##:'##::: ##:::: ##:                             \n");
    mvprintw(5 , ys, "                               #########: #####:::: ##:::: ##:                             \n");
    mvprintw(6 , ys, "                               ##.... ##: ##. ##::: ##:::: ##:                             \n");
    mvprintw(7 , ys, "                               ##:::: ##: ##:. ##:: ##:::: ##:                             \n");
    mvprintw(8 , ys, "                               ##:::: ##: ##::. ##:. #######::                             \n");
    mvprintw(9 , ys, "                              ..:::::..::..::::..:::.......:::                             \n");
    mvprintw(10, ys, "          :'######::'########:'##::::'##:'########::'########:'##::: ##:'########:         \n");
    mvprintw(11, ys, "          '##... ##:... ##..:: ##:::: ##: ##.... ##: ##.....:: ###:: ##:... ##..::         \n");
    mvprintw(12, ys, "           ##:::..::::: ##:::: ##:::: ##: ##:::: ##: ##::::::: ####: ##:::: ##::::         \n");
    mvprintw(13, ys, "          . ######::::: ##:::: ##:::: ##: ##:::: ##: ######::: ## ## ##:::: ##::::         \n");
    mvprintw(14, ys, "          :..... ##:::: ##:::: ##:::: ##: ##:::: ##: ##...:::: ##. ####:::: ##::::         \n");
    mvprintw(15, ys, "          '##::: ##:::: ##:::: ##:::: ##: ##:::: ##: ##::::::: ##:. ###:::: ##::::         \n");
    mvprintw(16, ys, "          . ######::::: ##::::. #######:: ########:: ########: ##::. ##:::: ##::::         \n");
    mvprintw(17, ys, "          :......::::::..::::::.......:::........:::........::..::::..:::::..:::::         \n");
    mvprintw(18, ys, " '######::'####:'##::::'##:'##::::'##:'##::::::::::'###::::'########::'#######::'########::\n");
    mvprintw(19, ys, "'##... ##:. ##:: ###::'###: ##:::: ##: ##:::::::::'## ##:::... ##..::'##.... ##: ##.... ##:\n");
    mvprintw(20, ys, " ##:::..::: ##:: ####'####: ##:::: ##: ##::::::::'##:. ##::::: ##:::: ##:::: ##: ##:::: ##:\n");
    mvprintw(21, ys, ". ######::: ##:: ## ### ##: ##:::: ##: ##:::::::'##:::. ##:::: ##:::: ##:::: ##: ########::\n");
    mvprintw(22, ys, ":..... ##:: ##:: ##. #: ##: ##:::: ##: ##::::::: #########:::: ##:::: ##:::: ##: ##.. ##:::\n");
    mvprintw(23, ys, "'##::: ##:: ##:: ##:.:: ##: ##:::: ##: ##::::::: ##.... ##:::: ##:::: ##:::: ##: ##::. ##::\n");
    mvprintw(24, ys, ". ######::'####: ##:::: ##:. #######:: ########: ##:::: ##:::: ##::::. #######:: ##:::. ##:\n");
    attroff(COLOR_PAIR(1));

    attron(A_BLINK | COLOR_PAIR(2));
    mvprintw(26, ConCol / 2 - 15, "++++++++++++++++++++++++++++++++");
    mvprintw(27, ConCol / 2 - 15, "| Press any key to continue... |");
    mvprintw(28, ConCol / 2 - 15, "++++++++++++++++++++++++++++++++");
    attroff(A_BLINK | COLOR_PAIR(2));
    box(stdscr, '+', '-');
    refresh();
}

string interface::input_in_main() {
    char s[1024];
    wscanw(main_downwin, "%[^\n]", s);                    // 这里对标的是 getline, 回车时结束读入
    return string(s);
}

void interface::output_in_main(string s) {
    wmove(main_downwin, 2, 1);
    wclrtoeol(main_downwin);
    wprintw(main_downwin, "%s", s.c_str());
    touchwin(stdscr);
    refresh();
}

// main interface
void interface::main_interface() {                         // manipulate on standard screen

    clear();
    refresh();

    main_upwin = subwin(stdscr, ConRow - 4, ConCol, 0, 0);
    main_downwin = subwin(stdscr, 5, ConCol, ConRow - 5, 0);
    box(main_upwin, '+', '.');
    box(main_downwin, '+', '.');
    wattron(main_upwin, COLOR_PAIR(2));
    mvwprintw(main_upwin, 3, ConCol / 2 - 15, "+++++++++++++++++++++++++++++");
    mvwprintw(main_upwin, 4, ConCol / 2 - 15, "|        1. New Game        |");
    mvwprintw(main_upwin, 5, ConCol / 2 - 15, "+++++++++++++++++++++++++++++");
    wattron(main_upwin, COLOR_PAIR(4));
    mvwprintw(main_upwin, 7, ConCol / 2 - 15, "+++++++++++++++++++++++++++++");
    mvwprintw(main_upwin, 8, ConCol / 2 - 15, "|        2. Load Game       |");
    mvwprintw(main_upwin, 9, ConCol / 2 - 15, "+++++++++++++++++++++++++++++");
    wattron(main_upwin, COLOR_PAIR(5));
    mvwprintw(main_upwin, 11, ConCol / 2 - 15, "+++++++++++++++++++++++++++++");
    mvwprintw(main_upwin, 12, ConCol / 2 - 15, "|        3. Tutorial        |");
    mvwprintw(main_upwin, 13, ConCol / 2 - 15, "+++++++++++++++++++++++++++++");
    wattron(main_upwin, COLOR_PAIR(1));
    mvwprintw(main_upwin, 15, ConCol / 2 - 15, "+++++++++++++++++++++++++++++");
    mvwprintw(main_upwin, 16, ConCol / 2 - 15, "|        4. Config          |");
    mvwprintw(main_upwin, 17, ConCol / 2 - 15, "+++++++++++++++++++++++++++++");
    wattron(main_upwin, COLOR_PAIR(3));
    mvwprintw(main_upwin, 19, ConCol / 2 - 15, "+++++++++++++++++++++++++++++");
    mvwprintw(main_upwin, 20, ConCol / 2 - 15, "|        q. [Exit]          |");
    mvwprintw(main_upwin, 21, ConCol / 2 - 15, "+++++++++++++++++++++++++++++");
    wattroff(main_upwin, COLOR_PAIR(3));

    touchwin(stdscr);
}

// tutorial interface

void interface::tut_print(WINDOW* w, string s) {
    wprintw(w, "%s", s.c_str());
    touchwin(tutscr);
    wrefresh(tutscr);
    usleep(10000);
}

void interface::tutorial_interface() {
    tutscr = newwin(ConRow, ConCol, 0, 0);
    
    WINDOW* tut_upwin = subwin(tutscr, ConRow - 4, ConCol - 12, 0, 6);
    WINDOW* tut_downwin = subwin(tutscr, 5, ConCol, ConRow - 5, 0);
    box(tutscr, '+', '.');
    box(tut_downwin, '+', '.');
    touchwin(tutscr);
    wrefresh(tutscr);
    wmove(tut_upwin, 1, 0);

    tut_print(tut_upwin, "\nWelcome to the text-based game of university life simulator!\n");
    tut_print(tut_upwin, "In this game, you will play as a freshman starting your journey at the prestigious HKU.\n");
    
    tut_print(tut_upwin, "\nAfter enrolled in your dream school ---- HKU, \n");
    tut_print(tut_upwin, "you feel excited to begin a new chapter of life and to explore all the opportunities comes with university education.\n");

    tut_print(tut_upwin, "\nAs a student, you will navigate through different events and situations that \
simulate various aspects of university life, \n");
    tut_print(tut_upwin, "such as [academics], [social activities], and [personal relationships].\n");

    wattron(tut_upwin, COLOR_PAIR(3));
    tut_print(tut_upwin, "\nEvery decision you make will have [consequences], and your ultimate goal is to \
achieve success while maintaining a balance between your academic and personal priorities.\n");
    wattroff(tut_upwin, COLOR_PAIR(3));

    tut_print(tut_upwin, "\nAre you ready to embark on this exciting and unpredictable journey as a freshman \
at HKU? Let's begin and see where life takes you on campus!\n");

    wmove(tut_downwin, 2, 2);
    wattron(tut_downwin, A_BLINK);
    tut_print(tut_downwin, "Press any key to return...");
    wattroff(tut_downwin, A_BLINK);

    getch();
}

void interface::game_interface() {

    gamescr = newwin(ConRow, ConCol, 0, 0);
    box(gamescr, '+', '.');
    wrefresh(gamescr);
    game_upwin = subwin(gamescr, ConRow - 4 - 2, ConCol - 25 - 4, 1, 2);
    game_downwin = subwin(gamescr, 5, ConCol, ConRow - 5, 0);
    game_rhtwin = subwin(gamescr, ConRow - 4, 25, 0, ConCol - 25);
//    box(game_upwin, '+', '.');
    box(game_downwin, '+', '.');
    box(game_rhtwin, '+', '.');
    scrollok(game_upwin, true);
    touchwin(gamescr);
    wrefresh(gamescr);
}

string interface::input_in_game_str(string prom) {
    wmove(game_downwin, 2, 2);
    wclrtoeol(game_downwin);
    wprintw(game_downwin, "%s", prom.c_str());
    touchwin(gamescr);
    wrefresh(gamescr);
    char s[1024];
    wscanw(game_downwin, "%[^\n]", s);  
    wclrtoeol(game_downwin);
    touchwin(gamescr);
    wrefresh(gamescr);
    return string(s);
}

int interface::input_in_game_int(string prom) {
    wmove(game_downwin, 2, 2);
    wclrtoeol(game_downwin);
    wprintw(game_downwin, "%s", prom.c_str());
    touchwin(gamescr);
    wrefresh(gamescr);
    int integer;
    wscanw(game_downwin, "%d", &integer); 
    wclrtoeol(game_downwin);
    touchwin(gamescr);
    wrefresh(gamescr); 
    return integer;
}

void interface::clearwin_in_game() {
    wclear(game_upwin);
    wmove(game_upwin, 0, 0);
    touchwin(gamescr);
    wrefresh(gamescr);
}

void interface::output_in_game(string s, int col, bool typ, bool udl, bool blk, bool bld, string des) {
    int eff = 0;
    if (udl)    eff |= A_UNDERLINE;
    if (blk)    eff |= A_BLINK;
    if (bld)    eff |= A_BOLD;
    wattron(game_upwin, COLOR_PAIR(col) | eff);
    if (typ) {
        for (int i = 0; i < s.size(); ++i) {
            wprintw(game_upwin, "%c", s[i]);
            touchwin(gamescr);
            wrefresh(gamescr);
            usleep(30000);
        }
    } else {
        wprintw(game_upwin, des.c_str(), s.c_str());
        touchwin(gamescr);
        wrefresh(gamescr);
    }
    wattroff(game_upwin, COLOR_PAIR(col) | eff);
}

string interface::input_in_save(string prom) {
    wmove(save_downwin, 2, 2);
    wclrtoeol(save_downwin);
    wprintw(save_downwin, "%s", prom.c_str());
    touchwin(savescr);
    wrefresh(savescr);
    char s[1024];
    wscanw(save_downwin, "%[^\n]", s);  
    wclrtoeol(save_downwin);
    touchwin(savescr);
    wrefresh(savescr);
    return string(s);
}

void interface::save_interface(string& filename) {                       

    savescr = newwin(ConRow, ConCol, 0, 0);
    box(savescr, '+', '.');
    wrefresh(savescr);

    save_upwin = subwin(savescr, ConRow - 4, ConCol, 0, 0);
    save_downwin = subwin(savescr, 5, ConCol, ConRow - 5, 0);
    box(save_upwin, '+', '.');
    box(save_downwin, '+', '.');

    FILE* fp;
    fp = fopen("Save#1.txt", "r");
    wattron(save_upwin, COLOR_PAIR(2));
    mvwprintw(save_upwin, 1, 2, "SAVE & QUIT page");
    if (fp == NULL) {
        mvwprintw(save_upwin, 3, ConCol / 2 - 15, "+++++++++++++++++++++++++++++");
        mvwprintw(save_upwin, 4, ConCol / 2 - 15, "|      Save #1: Empty       |");
        mvwprintw(save_upwin, 5, ConCol / 2 - 15, "+++++++++++++++++++++++++++++");
    } else {
        mvwprintw(save_upwin, 3, ConCol / 2 - 15, "+++++++++++++++++++++++++++++");
        mvwprintw(save_upwin, 4, ConCol / 2 - 15, "|      Save #1: Occupied    |");
        mvwprintw(save_upwin, 5, ConCol / 2 - 15, "+++++++++++++++++++++++++++++");
    }

    fp = fopen("Save#2.txt", "r");
    wattron(save_upwin, COLOR_PAIR(4));
    if (fp == NULL) {
        mvwprintw(save_upwin, 7, ConCol / 2 - 15, "+++++++++++++++++++++++++++++");
        mvwprintw(save_upwin, 8, ConCol / 2 - 15, "|      Save #2: Empty       |");
        mvwprintw(save_upwin, 9, ConCol / 2 - 15, "+++++++++++++++++++++++++++++");
    } else {
        mvwprintw(save_upwin, 7, ConCol / 2 - 15, "+++++++++++++++++++++++++++++");
        mvwprintw(save_upwin, 8, ConCol / 2 - 15, "|      Save #2: Occupied    |");
        mvwprintw(save_upwin, 9, ConCol / 2 - 15, "+++++++++++++++++++++++++++++");
    }

    fp = fopen("Save#3.txt", "r");
    wattron(save_upwin, COLOR_PAIR(5));
    if (fp == NULL) {
        mvwprintw(save_upwin, 11, ConCol / 2 - 15, "+++++++++++++++++++++++++++++");
        mvwprintw(save_upwin, 12, ConCol / 2 - 15, "|     Save #3: Empty        |");
        mvwprintw(save_upwin, 13, ConCol / 2 - 15, "+++++++++++++++++++++++++++++");
    } else {
        mvwprintw(save_upwin, 11, ConCol / 2 - 15, "+++++++++++++++++++++++++++++");
        mvwprintw(save_upwin, 12, ConCol / 2 - 15, "|     Save #3: Occupied     |");
        mvwprintw(save_upwin, 13, ConCol / 2 - 15, "+++++++++++++++++++++++++++++");
    }

    fp = fopen("Save#4.txt", "r");
    wattron(save_upwin, COLOR_PAIR(1));
    if (fp == NULL) {
        mvwprintw(save_upwin, 15, ConCol / 2 - 15, "+++++++++++++++++++++++++++++");
        mvwprintw(save_upwin, 16, ConCol / 2 - 15, "|     Save #4: Empty        |");
        mvwprintw(save_upwin, 17, ConCol / 2 - 15, "+++++++++++++++++++++++++++++");
    } else {
        mvwprintw(save_upwin, 15, ConCol / 2 - 15, "+++++++++++++++++++++++++++++");
        mvwprintw(save_upwin, 16, ConCol / 2 - 15, "|     Save #4: Occupied     |");
        mvwprintw(save_upwin, 17, ConCol / 2 - 15, "+++++++++++++++++++++++++++++");
    }
    wattrset(save_upwin, A_NORMAL);


    mvwprintw(save_upwin, 19, ConCol / 2 - 15, "+++++++++++++++++++++++++++++");
    mvwprintw(save_upwin, 20, ConCol / 2 - 15, "| [return]: Return to game  |");
    mvwprintw(save_upwin, 21, ConCol / 2 - 15, "| [quit]: End the game      |");
    mvwprintw(save_upwin, 22, ConCol / 2 - 15, "| [save]: Save current game |");
    mvwprintw(save_upwin, 23, ConCol / 2 - 15, "+++++++++++++++++++++++++++++");

    touchwin(savescr);

    while (true) {
        string op = input_in_save("Enter your command: (above is the command list): ");
        while (op != "return" && op != "quit" && op != "save") {
            op = input_in_save("Invalid input. Do you want to [return], [quit] or [save]? ");
        }   
        if (op == "return") {
            return;
        } 
        if (op == "quit") {
            op = input_in_save(" Are you sure to exit? (Y/N): ");
            if (op == "Y") {
                end_config();
            }
        }
        if (op == "save") {
            while (true) {
                op = input_in_save("Please select a saving unit (1-4): ");
                while (op != "1" && op != "2" && op != "3" && op != "4")
                    op = input_in_save("Invalid input. Please enter a number in [1, 4]: ");
                string fileName = "Save#" + op + ".txt";
                FILE* fp = fopen(fileName.c_str(), "r");
                if (fp == NULL) {
                    filename = fileName;
                    break;
                } else {
                    op = input_in_save("This unit is already occupied. Do you want to overwrite it? (Y/N): ");
                    if (op == "Y") {
                        filename = fileName;
                        break;
                    }
                }
            }
        }
    }

}

string interface::input_in_load(string prom) {
    wmove(load_downwin, 2, 2);
    wclrtoeol(load_downwin);
    wprintw(load_downwin, "%s", prom.c_str());
    touchwin(loadscr);
    wrefresh(loadscr);
    char s[1024];
    wscanw(load_downwin, "%[^\n]", s);  
    wclrtoeol(load_downwin);
    touchwin(loadscr);
    wrefresh(loadscr);
    return string(s);
}

void interface::load_interface(string& filename) {                  

    loadscr = newwin(ConRow, ConCol, 0, 0);
    box(loadscr, '+', '.');
    wrefresh(loadscr);

    load_upwin = subwin(loadscr, ConRow - 4, ConCol, 0, 0);
    load_downwin = subwin(loadscr, 5, ConCol, ConRow - 5, 0);
    box(load_upwin, '+', '.');
    box(load_downwin, '+', '.');

    FILE* fp;
    fp = fopen("Save#1.txt", "r");
    wattron(load_upwin, COLOR_PAIR(2));
    mvwprintw(load_upwin, 1, 2, "LOAD page");
    if (fp == NULL) {
        mvwprintw(load_upwin, 3, ConCol / 2 - 15, "+++++++++++++++++++++++++++++");
        mvwprintw(load_upwin, 4, ConCol / 2 - 15, "|      Save #1: Empty       |");
        mvwprintw(load_upwin, 5, ConCol / 2 - 15, "+++++++++++++++++++++++++++++");
    } else {
        mvwprintw(load_upwin, 3, ConCol / 2 - 15, "+++++++++++++++++++++++++++++");
        mvwprintw(load_upwin, 4, ConCol / 2 - 15, "|      Save #1: Occupied    |");
        mvwprintw(load_upwin, 5, ConCol / 2 - 15, "+++++++++++++++++++++++++++++");
    }

    fp = fopen("Save#2.txt", "r");
    wattron(load_upwin, COLOR_PAIR(4));
    if (fp == NULL) {
        mvwprintw(load_upwin, 7, ConCol / 2 - 15, "+++++++++++++++++++++++++++++");
        mvwprintw(load_upwin, 8, ConCol / 2 - 15, "|      Save #2: Empty       |");
        mvwprintw(load_upwin, 9, ConCol / 2 - 15, "+++++++++++++++++++++++++++++");
    } else {
        mvwprintw(load_upwin, 7, ConCol / 2 - 15, "+++++++++++++++++++++++++++++");
        mvwprintw(load_upwin, 8, ConCol / 2 - 15, "|      Save #2: Occupied    |");
        mvwprintw(load_upwin, 9, ConCol / 2 - 15, "+++++++++++++++++++++++++++++");
    }

    fp = fopen("Save#3.txt", "r");
    wattron(load_upwin, COLOR_PAIR(5));
    if (fp == NULL) {
        mvwprintw(load_upwin, 11, ConCol / 2 - 15, "+++++++++++++++++++++++++++++");
        mvwprintw(load_upwin, 12, ConCol / 2 - 15, "|     Save #3: Empty        |");
        mvwprintw(load_upwin, 13, ConCol / 2 - 15, "+++++++++++++++++++++++++++++");
    } else {
        mvwprintw(load_upwin, 11, ConCol / 2 - 15, "+++++++++++++++++++++++++++++");
        mvwprintw(load_upwin, 12, ConCol / 2 - 15, "|     Save #3: Occupied     |");
        mvwprintw(load_upwin, 13, ConCol / 2 - 15, "+++++++++++++++++++++++++++++");
    }

    fp = fopen("Save#4.txt", "r");
    wattron(load_upwin, COLOR_PAIR(1));
    if (fp == NULL) {
        mvwprintw(load_upwin, 15, ConCol / 2 - 15, "+++++++++++++++++++++++++++++");
        mvwprintw(load_upwin, 16, ConCol / 2 - 15, "|     Save #4: Empty        |");
        mvwprintw(load_upwin, 17, ConCol / 2 - 15, "+++++++++++++++++++++++++++++");
    } else {
        mvwprintw(load_upwin, 15, ConCol / 2 - 15, "+++++++++++++++++++++++++++++");
        mvwprintw(load_upwin, 16, ConCol / 2 - 15, "|     Save #4: Occupied     |");
        mvwprintw(load_upwin, 17, ConCol / 2 - 15, "+++++++++++++++++++++++++++++");
    }
    wattrset(load_upwin, A_NORMAL);

    mvwprintw(load_upwin, 19, ConCol / 2 - 15, "+++++++++++++++++++++++++++++");
    mvwprintw(load_upwin, 20, ConCol / 2 - 15, "| [return]: Return to main  |");
    mvwprintw(load_upwin, 21, ConCol / 2 - 15, "| [quit]: End the game      |");
    mvwprintw(load_upwin, 22, ConCol / 2 - 15, "| [load]: Load any game...  |");
    mvwprintw(load_upwin, 23, ConCol / 2 - 15, "+++++++++++++++++++++++++++++");

    touchwin(loadscr);

    while (true) {
        string op = input_in_load("Enter your command: (above is the command list): ");
        while (op != "return" && op != "quit" && op != "load") {
            op = input_in_load("Invalid input. Do you want to [return], [quit] or [load]? ");
        }
        if (op == "return") {
            return;
        } 
        if (op == "quit") {
            op = input_in_load(" Are you sure to exit? (Y/N): ");
            if (op == "Y") {
                end_config();
            }
            return;
        }
        if (op == "load") {
            op = input_in_load("Please select a loading unit (1-4): ");
            string fileName = "Save#" + op + ".txt";
            FILE* fp = fopen(fileName.c_str(), "r");
            while ((op != "1" && op != "2" && op != "3" && op != "4") || fp == NULL) {
                op = input_in_load("Invalid input. Please select an [occupied] unit: ");
                fileName = "Save#" + op + ".txt";
                fp = fopen(fileName.c_str(), "r");
            }

            op = input_in_load(" Are you sure to load " + fileName + " ? (Y/N): ");
            if (op == "Y") {
                filename = fileName;
                return;
            }
        }
    }
}
