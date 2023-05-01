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
    sleep(1);
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

int interface::select_save_file() {
    int selected_save = 1;
    while (true) {
        clear();
        mvprintw(0, 0, "Select a save file:");
        for (int i = 1; i <= 4; ++i) {
            if (i == selected_save) {
                attron(A_REVERSE);
            }
            mvprintw(i, 0, "Save %d", i);
            if (i == selected_save) {
                attroff(A_REVERSE);
            }
        }
        int ch = getch();
        if (ch == KEY_DOWN || ch == 's') {
            selected_save = (selected_save % 4) + 1;
        } else if (ch == KEY_UP || ch == 'w') {
            selected_save = ((selected_save - 2) % 4) + 1;
        } else if (ch == '\n' || ch == KEY_ENTER) {
            break;
        }
    }
    return selected_save;
}
void interface::save_game(Player &p) {
    ofstream saveFile("save.txt");
    if (saveFile.is_open()) {
        saveFile << p.name << endl
                 << p.iq << endl
                 << p.eq << endl
                 << p.courage << endl
                 << p.luck << endl
                 << p.sex << endl
                 << p.gpa << endl;
    }
    saveFile.close();
}
void interface::load_game(Player &p) {
    ifstream saveFile("save.txt");
    if (saveFile.is_open()) {
        getline(saveFile, p.name);
        saveFile >> p.iq
                 >> p.eq
                 >> p.courage
                 >> p.luck
                 >> p.sex
                 >> p.gpa;
    }
    saveFile.close();
}

