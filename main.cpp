#include <iostream>
#include <string>
#include <cstdlib>
#include <ctime>
#include <unistd.h>
#include <fstream>

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
Minor m6(3, 0, 0);

void initRandomEvents() {       // initialize the random events
    randomEvent.clear();
    randomEvent.push_back((Event*)&d1);
    randomEvent.push_back((Event*)&d2);
    randomEvent.push_back((Event*)&d3);
    randomEvent.push_back((Event*)&d4);
    randomEvent.push_back((Event*)&d5);
    randomEvent.push_back((Event*)&d6);
    randomEvent.push_back((Event*)&d7);
}

void initMainEvents() {         // initialize the main events (challenges)
    mainEvent.clear();
    mainEvent.push_back((Event*)&m1);
    mainEvent.push_back((Event*)&m2);
    mainEvent.push_back((Event*)&m3);
    mainEvent.push_back((Event*)&m4);
    mainEvent.push_back((Event*)&m5);
    mainEvent.push_back((Event*)&m6);
}

// the saving process: the status of the current game could be divided in 3 catagories:
// 1: player's information (parameter player& p)
// 2: current time: (parameter year, sem and week)
// 3. current event process: the global vectors randomEvent & mainEvent
void checkSave(interface& INT, player& p, int year, int sem, int week) {
    string fileName = "NULL";
    bool quit = false;
    p.game_config(INT, fileName, quit);
    if (fileName != "NULL") {
        ofstream fout;
        fout.open(fileName.c_str());

// attributes
        fout << p.getName() << endl;
        fout << p.getIq() << endl;
        fout << p.getEq() << endl;
        fout << p.getCourage() << endl;
        fout << p.getLuck() << endl;
        fout << p.getSex() << endl;

        fout << p.getMoney() << endl;
        fout << p.getPressure() << endl;

// grades
        fout << p.getsGPA() << endl;
        
        double g[10];
        int cnt;
        p.getGrades(g, cnt);
        fout << cnt << endl;
        for (int i = 0; i < cnt; ++i)   fout << g[i] << endl;

// events
        fout << randomEvent[0]->getProcess() << endl;
        fout << randomEvent[1]->getProcess() << endl;
        fout << randomEvent[2]->getProcess() << endl;
        fout << randomEvent[3]->getProcess() << endl;
        fout << randomEvent[4]->getProcess() << endl;
        fout << randomEvent[5]->getProcess() << endl;
        fout << randomEvent[6]->getProcess() << endl;

        fout << mainEvent[0]->getProcess() << endl;
        fout << mainEvent[1]->getProcess() << endl;
        fout << mainEvent[2]->getProcess() << endl;
        fout << mainEvent[3]->getProcess() << endl;
        fout << mainEvent[4]->getProcess() << endl;
        fout << mainEvent[5]->getProcess() << endl;
// places
        bool vis[10];
        p.getvisited(vis);
        for (int i = 0; i < 10; ++i)
            fout << vis[i] << endl;
        string unl[10];
        p.getUnlocked(unl, cnt);
        fout << cnt << endl;
        for (int i = 0; i < cnt; ++i)
            fout << unl[i] << endl;
        int part[10];
        p.getParttimeid(part, cnt);
        fout << cnt << endl;
        for (int i = 0; i < cnt; ++i)
            fout << part[i] << endl;
        
// date
        if (week == 14) {
            if (sem == 1) {
                sem = 2, week = 1;
            }
            if (sem == 2) {
                year += 1, sem = 1, week = 1;
            }
        } else {
            week += 1;
        }
        fout << year << endl;
        fout << sem << endl;
        fout << week << endl;
        fout.close();
    }
    if (quit) {
        exit(0);
    }
}

// the whole simulation process
// it takes time and player as input, and continue to simulate at that time
void simulate(interface& INT, int year, int sem, int week, player& p) {
    if (year == 5) { // in fact: 5
        int mainProcess[5] = {mainEvent[0]->getProcess(), mainEvent[1]->getProcess(), 
                              mainEvent[2]->getProcess(), mainEvent[3]->getProcess(), 
                              mainEvent[4]->getProcess()};
        p.simulate_semester_end(INT, randomEvent[2]->getProcess(), randomEvent[3]->getProcess(), mainProcess, 0);
        getch();  
        return;
    }
    if (week == 1) {
        p.simulate_semester_begin();
    }
    if (week == 14) {
        int mainProcess[5] = {mainEvent[0]->getProcess(), mainEvent[1]->getProcess(), 
                              mainEvent[2]->getProcess(), mainEvent[3]->getProcess(), 
                              mainEvent[4]->getProcess()};
        p.simulate_semester_end(INT, randomEvent[2]->getProcess(), randomEvent[3]->getProcess(), mainProcess, sem);      
        mainEvent[0]->setProcess(mainProcess[0]);
        mainEvent[1]->setProcess(mainProcess[1]);
        initRandomEvents();
        checkSave(INT, p, year, sem, week);
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
    checkSave(INT, p, year, sem, week);
    simulate(INT, year, sem, week + 1, p);
}

// create and initialize a new game
void new_game(interface& INT) {
    INT.game_interface();
    player newPlayer;
    newPlayer.init(INT);
    srand(time(0));
    simulate(INT, 1, 1, 1, newPlayer);
}

// load a game
void load_game(interface& INT) {
    srand(time(0));
    string fileName = "NULL";
    INT.load_interface(fileName);
    if (fileName != "NULL") {
        player loadplayer;
        loadplayer.initLandscape(INT);
        INT.game_interface();
        ifstream fin;
        fin.open(fileName.c_str());

        string dname;
        getline(fin, dname);
        loadplayer.setName(dname);

    
        int iq;
        fin >> iq;
        loadplayer.setIq(iq);


        int eq;
        fin >> eq;
        loadplayer.setEq(eq);


        int courage;
        fin >> courage;
        loadplayer.setCourage(courage);

        int luck;
        fin >> luck;
        loadplayer.setLuck(luck);

        int sex;
        fin >> sex;
        loadplayer.setSex(sex);

        int money;
        fin >> money;
        loadplayer.setMoney(money);

        int pressure;
        fin >> pressure;
        loadplayer.setPressure(pressure);

        double sgpa;
        fin >> sgpa;
        loadplayer.setsGPA(sgpa);

        double g[10];
        int cnt;
        fin >> cnt;
        for (int i = 0; i < cnt; ++i)   fin >> g[i];
        loadplayer.setGrades(g, cnt);

        int pro;
        fin >> pro;
        randomEvent[0]->setProcess(pro);
        fin >> pro;
        randomEvent[1]->setProcess(pro);
        fin >> pro;
        randomEvent[2]->setProcess(pro);
        fin >> pro;
        randomEvent[3]->setProcess(pro);
        fin >> pro;
        randomEvent[4]->setProcess(pro);
        fin >> pro;
        randomEvent[5]->setProcess(pro);
        fin >> pro;
        randomEvent[6]->setProcess(pro);

        fin >> pro;
        mainEvent[0]->setProcess(pro);
        fin >> pro;
        mainEvent[1]->setProcess(pro);
        fin >> pro;
        mainEvent[2]->setProcess(pro);
        fin >> pro;
        mainEvent[3]->setProcess(pro);
        fin >> pro;
        mainEvent[4]->setProcess(pro);
        fin >> pro;
        mainEvent[5]->setProcess(pro);

        bool vis[10];
        for (int i = 0; i < 10; ++i)
            fin >> vis[i];
        loadplayer.setvisited(vis);

        
        string unl[10];
        fin >> cnt;
        fin.ignore();
        for (int i = 0; i < cnt; ++i)   getline(fin, unl[i]);
        loadplayer.setUnlocked(unl, cnt);
        

        int part[10];
        fin >> cnt;
        for (int i = 0; i < cnt; ++i)
            fin >> part[i];
        loadplayer.setParttimeid(part, cnt);

        int year, sem, week;
        fin >> year >> sem >> week;
        fin.close();
        simulate(INT, year, sem, week, loadplayer);
    }
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
        INT.output_in_main(" Your command here: ");
        string op = INT.input_in_main();
        if (op == "4") {
            INT.output_in_main(" Sorry! Config module is still in development... (Press any key to proceed...)");
            getch();
        } else if (op == "2") {
            load_game(INT);
        } else if (op == "1") {
            new_game(INT);
        } else if (op == "3") {
            INT.tutorial_interface();
        } else if (op == "q") {
            INT.output_in_main(" Are you sure to exit? (Y/N): ");
            op = INT.input_in_main();
            if (op == "Y") 
                break;
        } else {
            INT.output_in_main(" Invalid input! (Press any key to proceed...)");
            getch();
        }
    }
    
    INT.end_config();

    return 0;
}
