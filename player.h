#ifndef PLAYER_H
#define PLAYER_H

#include <string>
#include <vector>
#include <ncurses.h>

#include "interface.h"
#include "item.h"

// player is the object that contains all the information about player (therefore it is part of the game status)
// it also has the function to simulate in the basic time unit (week) of this game
class player {
// time
    int ord;
    int mon;

// player's attributes
    std::string name;
    int iq;            
    int eq;              
    int courage;          
    int luck;              
    int sex;                // 0/1 for male/female
    int money;
    double gpa;             // GPA


    bool specialSkill[10]; 

// player's visited places
    bool visited[10];
    vector<int> parttimeId;
    vector<string> unlockedLandmarks;

// player's grades and pressure
    double expectedGrades;
    int pressure;
    vector<double> viewYourGrades;
    
    void initName(interface&);          // initialize player's name
    void initSex(interface&);           // initialize player's gender
    void initVal(interface&);           // initialize player's beginning attribute
    void initSkill(interface&);         // ... 

    string study_prompt();              // return a string that indicate player's study status
    string doelse_prompt();             // ...

    void go_somewhere_else(interface&, bool);           // simulate when player decides to go out
    void explore_the_place(interface&, string, bool);   // simulate when player decides to go to a specific place
    bool do_part_time(interface&, bool);                // simulate when player dicides to do part-time job
    void horseracing(interface&);                       // simulate when player participate in horseracing
    bool search_for_rd(int);                            // auxilary function to decide whether a place provides part-time job
    void surf_the_internet(interface&, bool);           // simulate when player decides to surf on internet
    void shopping(interface&, string, bool);            // simulate when player decides to go shopping
    void encounterItems(item, interface&, bool);        // simulate when player encounters items (the everyday events)
    string grade_converter(double);                     // convert player's grades to letter grade

public:

    void initLandscape(interface&);                     // initialize different landscapes that player could explore
    void init(interface&);                              // the whole initializing process
    void printTranscript(interface&);                   // print player's transcript that shows his attributes

// getters
    std::string getName() const;                    
    double getsGPA() const;
    int getIq() const;
    int getEq() const;
    int getCourage() const;
    int getLuck() const;
    int getSex() const;
    int getMoney() const;
    int getPressure() const;
    void getGrades(double*, int&);
    void getvisited(bool*);
    void getParttimeid(int*, int&);
    void getUnlocked(string*, int&);
// setters
    void setName(std::string);
    void setsGPA(double);
    void setIq(int);
    void setEq(int);
    void setCourage(int);
    void setLuck(int);
    void setSex(int);
    void setMoney(int);
    void setPressure(int);
    void setGrades(double*, int);
    void setvisited(bool*);
    void setParttimeid(int*, int);
    void setUnlocked(string*, int);
    

    void game_config(interface&, string&, bool&);  // called when a week is completed, connect to the save&load module
    void printValue(interface&);                   // handle the attribute shown in the right column

    void simulate_action(interface&, bool, bool);       // simulate when player make a choice in a normal week
    void simulate_ordinary_week(interface&, int, int, bool, bool);  // simulate player's action in a normal week
    void simulate_semester_begin();                     // initialize when a new semester is begin
    void simulate_assessment_period(interface&);        // simulate the assessment period
    void simulate_semester_end(interface&, int, int, int*, int);    // modify the change of attribute when a semester is finished

};

#endif