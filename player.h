#ifndef PLAYER
#define PLAYER

#include <string>
#include <ncurses.h>

#include "interface.h"

class player {
    std::string name;
    int iq;                 // 智商 intelligence
    int eq;                 // 魅力 charisma
    int courage;            // 勇气 courage
    int luck;               // 运气 luck
    int sex;                // 0/1 for male/female

    bool specialSkill[10];  // specialSkill[1]: Money talks: Don't worry. You got money. A lot!
                            // specialSkill[2]: to be added...
public:
    void initName(interface&);
    void initSex(interface&);
    void initVal(interface&);
    void initSkill(interface&);
    void init(interface&);

    void printTranscript(interface&);
    void colorPrint(std::string, int);  // need to convert to Linux mode
/*
    void modifyIq(int d);
    void modifyEq(int d);
    void modifyCourage(int d);
    void modifyLuck(int d);
    void modifySpecialSkill(int id, int d, std::string reason); 
*/
};

#endif