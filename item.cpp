#include <string>
#include "item.h"

using namespace std;

item::item(int _0, int _1, int _2, int _3, int _4, int _5, std::string _n, std::string _s) :
    cost(_0), diq(_1), deq(_2), dcourage(_3), dluck(_4), dskill(_5), name(_n), des(_s) {} 
    
int item::getCost() { return cost; }
int item::addiq() { return diq; }
int item::addeq() { return deq; }
int item::addcourage() { return dcourage; }
int item::addluck() { return dluck; }
int item::addskill() { return dskill; }

string item::getName() { return name; }
string item::description() { return des; }
string item::positiveEffect() {
    string res = "\n";
    if (diq > 0)
        res += "Your IQ (intelligence) has improved! [IQ++]\n";
    if (deq > 0)
        res += "Your EQ (charisma) has improved! [EQ++]\n";
    if (dcourage > 0)
        res += "Your courage has improved! [courage++]\n";
    if (dluck > 0)
        res += "You've somehow been luckier... [luck++]\n";
    if (dskill > 0)
        res += "You've acquired a new skill! [Skill " + to_string(dskill) + " ]\n";
    if (cost < 0)
        res += "You've earned [" + to_string(-cost) + "] $\n\n";
    return res;
}

string item::negativeEffect() {
    string res = "\n";
    if (diq < 0)
        res += "Your IQ (intelligence) has decreased... [IQ--]\n";
    if (deq < 0)
        res += "Your EQ (charisma) has decreased... [EQ--]\n";
    if (dcourage < 0)
        res += "Your courage has decreased... [courage--]\n";
    if (dluck < 0)
        res += "You've somehow been unluckier... [luck--]\n";
    if (dskill < 0)
        res += "You've lost a skill... [Skill " + to_string(-dskill) + " ]\n";
    if (cost > 0)
        res += "This have cost you [" + to_string(cost) + "] $\n\n";
    return res;
}
