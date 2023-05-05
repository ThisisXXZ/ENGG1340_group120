#ifndef ITEM
#define ITEM

#include <string>

// item is a object that could interact with players, and could influence player's attributes
class item {
    int cost;
    int diq;
    int deq;
    int dcourage;
    int dluck;
    int dskill;       // +[id]: acquire a new skill; -[id]: lost a skill

    std::string name;
    std::string des;  // description
public:
    item(int, int, int, int, int, int, std::string, std::string);
// getters for items
    int getCost();      
    int addiq();
    int addeq();
    int addcourage();
    int addluck();
    int addskill();
    std::string getName();
    std::string description();
// return string describing this item(event)'s positive/negative effects
    std::string positiveEffect();
    std::string negativeEffect();
};

#endif