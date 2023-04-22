#ifndef INTERFACE
#define INTERFACE

#include <string>
#include <ncurses.h>
#include <unistd.h>

using namespace std;

int ConRow, ConCol;

WINDOW* main_upwin;
WINDOW* main_downwin;                   // for main interface: subscrs for stdscr
WINDOW* gamescr;
WINDOW* tutscr;                         // for tutorial interface

// initializa color module and obtain the size of terminal
// suggested size: 30 * 120

void color_config() { 
    if (has_colors()) {
        start_color();
        init_pair(1, COLOR_CYAN, COLOR_BLACK);
        init_pair(2, COLOR_GREEN, COLOR_BLACK);
        init_pair(3, COLOR_RED, COLOR_BLACK);
        init_pair(4, COLOR_YELLOW, COLOR_BLACK);
        init_pair(5, COLOR_MAGENTA, COLOR_BLACK);
    }
}

void initial_config() {
    color_config();
    getmaxyx(stdscr, ConRow, ConCol);
}

// title interface

void title_interface() {                  // manipulate on standard screen
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

string input_in_main() {
    char s[1024];
    wscanw(main_downwin, "%[^\n]", s);           // 这里对标的是 getline, 回车时结束读入
    return string(s);
}

void output_in_main(string s) {
    wmove(main_downwin, 2, 1);
    wclrtoeol(main_downwin);
    wprintw(main_downwin, "%s", s.c_str());
    touchwin(stdscr);
    refresh();
}

// main interface
void main_interface() {                         // manipulate on standard screen

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

void tut_print(WINDOW* w, string s) {
    wprintw(w, "%s", s.c_str());
    touchwin(tutscr);
    wrefresh(tutscr);
    sleep(1);
}

void tutorial_interface() {
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

#endif