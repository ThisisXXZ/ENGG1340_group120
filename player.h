#ifndef PLAYER_H
#define PLAYER_H

#include <string>
#include <ncurses.h>

#include "interface.h"

class player {
    std::string name;
    int iq;                 // 智商 intelligence
    int eq;                 // 魅力 charisma
    int courage;            // 勇气 courage
    int luck;               // 运气 luck
    int sex;               // 0/1 for male/female
    double gpa;             // GPA


    bool specialSkill[10];  // specialSkill[1]: Money talks: Don't worry. You got money. A lot!
                            // specialSkill[2]: to be added...
    
    double expectedGrades;
    int pressure;
    double viewYourGrades[10];

    void initName(interface&);
    void initSex(interface&);
    void initVal(interface&);
    void initSkill(interface&);       

    string study_prompt();
    string doelse_prompt();

    void surf_the_internet(interface&);
    void simulate_ordinary_week(interface&, int, int);

public:
    
    void init(interface&);
    void printTranscript(interface&);
    void printValue(WINDOW*, WINDOW*, string, int);      // break the abstraction a little bit

    void simulate_first_semester(interface&);
    double getGPA() const;
    int getIq() const;
    int getEq() const;
    int getCourage() const;
    int getLuck() const;
    int getSex() const;
    std::string getName() const;
    void printValue(WINDOW*, WINDOW*, string, int);      // break the abstraction a little bit

    void simulate_first_semester(interface&);
/*
    void modifyIq(int d);
    void modifyEq(int d);
    void modifyCourage(int d);
    void modifyLuck(int d);
    void modifySpecialSkill(int id, int d, std::string reason); 
*/
    void save_game(const string &filename);
    bool load_game(const string &filename);
};

#endif
