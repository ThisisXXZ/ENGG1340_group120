#ifndef PLAYER_H
#define PLAYER_H

#include <string>
#include <ncurses.h>

#include "interface.h"
#include "item.h"

class player {

    int ord;
    int mon;

    std::string name;
    int iq;                 // 智商 intelligence
    int eq;                 // 魅力 charisma
    int courage;            // 勇气 courage
    int luck;               // 运气 luck
    int sex;                // 0/1 for male/female
    int money;
    double gpa;             // GPA


    bool specialSkill[10];  // specialSkill[1]: Money talks: Don't worry. You got money. A lot!
                            // specialSkill[2]: to be added...
    
    double expectedGrades;
    int pressure;
    double viewYourGrades[10];

    void initLandscape(interface&);
    void initName(interface&);
    void initSex(interface&);
    void initVal(interface&);
    void initSkill(interface&);       

    string study_prompt();
    string doelse_prompt();

    
    void go_somewhere_else(interface&, bool);
    void explore_the_place(interface&, string, bool);
    bool do_part_time(interface&, bool);
    void horseracing(interface&);
    void shopping(interface&, string, bool);

   
    
    void encounterItems(item, interface&, bool);

public:
    
    void init(interface&);
    void printTranscript(interface&);

// getters
    double getsGPA() const;
    int getIq() const;
    int getEq() const;
    int getCourage() const;
    int getLuck() const;
    int getSex() const;
    int getPressure() const;
// setters
    void setsGPA(double);
    void setIq(int);
    void setEq(int);
    void setCourage(int);
    void setLuck(int);
    void setPressure(int);

    std::string getName() const;
    void printValue(interface&);      // break the abstraction a little bit

    void surf_the_internet(interface&, bool);

    void simulate_action(interface&, bool, bool);
    void simulate_ordinary_week(interface&, int, int, bool, bool);
    void simulate_semester_begin();
    void simulate_semester_end();

};

#endif