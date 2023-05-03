#include <iostream>
#include <string>
#include <cstdlib>
#include <ctime>
#include <unistd.h>

#include "event.h"
#include "player.h"
#include "interface.h"

using namespace std;

const int t[2][15] = {{0, 9, 9, 9, 9, 10, 10, 10, 10, 11, 11, 11, 11, 12}, 
                         {0, 2, 2, 2, 2, 3, 3, 3, 3, 4, 4, 4, 4, 5}}; 
                         
vector <Event*> randomEvent;
vector <Event*> mainEvent;

StrugglingInClass d1(0, 0, 0);
MissingDeadline d2(0, 0, 0);
Scholarships d3(0, 0, 0);
Depression d4(0, 0, 0);
WatchDanceShow d5(0, 0, 0);
WatchDebateCompetition d6(0, 0, 0);
GotoChurch d7(0, 0, 0);

StudyAbroad m1(1, 2, 0);
InternshipOrCoop m2(2, 0, 0);
JoiningClubs m3(1, 0, 0);
Relationship m4(2, 0, 0);
GraduateCapstone m5(4, 0, 0);

void initRandomEvents() {
    randomEvent.clear();
    randomEvent.push_back((Event*)&d1);
    randomEvent.push_back((Event*)&d2);
    randomEvent.push_back((Event*)&d3);
    randomEvent.push_back((Event*)&d4);
    randomEvent.push_back((Event*)&d5);
    randomEvent.push_back((Event*)&d6);
    randomEvent.push_back((Event*)&d7);
}

void initMainEvents() {
    mainEvent.clear();
    mainEvent.push_back((Event*)&m1);
    mainEvent.push_back((Event*)&m2);
    mainEvent.push_back((Event*)&m3);
    mainEvent.push_back((Event*)&m4);
    mainEvent.push_back((Event*)&m5);
}

void simulate(interface& INT, int year, int sem, int week, player& p) {
    if (year == 2) { // in fact: 5
        // ...
        return;
    }
    if (week == 1) {
        p.simulate_semester_begin();
    }
    if (week == 14) {
        // ...
        p.simulate_semester_end();
        initRandomEvents();
        if (sem == 1) 
            simulate(INT, year, 2, 1, p);
        if (sem == 2)
            simulate(INT, year + 1, 1, 1, p);
        return;
    }
    
    int ord = (week % 4 == 0) ? 4 : week % 4;
    p.simulate_ordinary_week(INT, ord, t[sem - 1][week], week == 6, week == 13);

    // main event

    // random event
    if (!randomEvent[rand() % randomEvent.size()]->applyEvent(p, INT))
        p.simulate_action(INT, week == 6, week == 13);

    for (int i = 0; i < mainEvent.size(); ++i) {
        if (mainEvent[i]->checktime(year, sem, week))
            mainEvent[i]->applyEvent(p, INT);
    }

    getch();
    simulate(INT, year, sem, week + 1, p);
}

void new_game(interface& INT) {
    INT.game_interface();
    getch();                // 过场动画? 
    player newPlayer;
//    newPlayer.init(INT);
//    newPlayer.simulate_first_semester(INT);
    srand(time(0));
    simulate(INT, 1, 2, 13, newPlayer);
}

int main() {

    interface INT;

    INT.initial_config();
    INT.title_interface();
    initRandomEvents();
    initMainEvents();

    getch();
    
    INT.main_interface();
    while (true) {
        INT.output_in_main(" Your prompt here: ");
        string op = INT.input_in_main();
        if (op == "2" || op == "4")
                break;
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
