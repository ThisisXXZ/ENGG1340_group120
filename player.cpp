#include <string>
#include <cstdlib>
#include <ctime>
#include <unistd.h>
#include <map>
#include <vector>
#include <algorithm>

#include "player.h"
#include "interface.h"
#include "item.h"

using namespace std;

// GETTERS

string player::getName() const {
    return name;
}

int player::getIq() const {
    return iq;
}

int player::getEq() const {
    return eq;
}

double player::getsGPA() const {
    return expectedGrades;
}
int player::getSex() const {
    return sex;
}
int player::getCourage() const {
    return courage;
}

int player::getLuck() const {
    return luck;
}

int player::getMoney() const {
    return money;
}

int player::getPressure() const {
    return pressure;
}

void player::getGrades(double* g, int& num) {
    for (int i = 0; i < viewYourGrades.size(); ++i)
        g[i] = viewYourGrades[i];
    num = viewYourGrades.size();
}

void player::getvisited(bool* _v) {
    for (int i = 0; i < 10; ++i)
        _v[i] = visited[i];
}

void player::getUnlocked(string* _u, int& num) {
    for (int i = 0; i < unlockedLandmarks.size(); ++i)
        _u[i] = unlockedLandmarks[i];
    num = unlockedLandmarks.size();
}

void player::getParttimeid(int* pt, int& num) {
    for (int i = 0; i < parttimeId.size(); ++i)
        pt[i] = parttimeId[i];
    num = parttimeId.size();
}
    

// SETTERS
void player::setName(string d) {
    name = d;
}

void player::setIq(int d) {
    iq = d;
}

void player::setEq(int d) {
    eq = d;
}

void player::setsGPA(double d) {
    expectedGrades = d;
}

void player::setCourage(int d) {
    courage = d;
}

void player::setLuck(int d) {
    luck = d;
}

void player::setSex(int d) {
    sex = d;
}

void player::setMoney(int d) {
    money = d;
}

void player::setPressure(int d) {
    pressure = d;
}

void player::setGrades(double* g, int num) {
    viewYourGrades.clear();
    for (int i = 0; i < num; ++i)
        viewYourGrades.push_back(g[i]);
}

void player::setvisited(bool* g) {
    for (int i = 0; i < 10; ++i)
        visited[i] = g[i];
}

void player::setUnlocked(string* g, int num) {
    unlockedLandmarks.clear();
    for (int i = 0; i < num; ++i)
        unlockedLandmarks.push_back(g[i]);
}

void player::setParttimeid(int* g, int num) {
    parttimeId.clear();
    for (int i = 0; i < num; ++i)
        parttimeId.push_back(g[i]);
}

// INIT_MODULE

string month[] = {"", "January", "February", "March", 
                    "April", "May", "June", "July", 
                    "August", "September", "October", 
                    "November", "December"};

string order[] = {"", "first", "second", "third", "fourth"};

void player::initName(interface& INT) {
    string text = "What is your name? (English only)\n";
    INT.output_in_game(text, 4, true, true);
    name = INT.input_in_game_str();
}

void player::initSex(interface& INT) {
    string text = "\nWhat is your gender?\n";
    INT.output_in_game(text, 4, true, true);
    text = "(0 for male, 1 for female. 2 if you don't care and want to set it randomly)\n";
    INT.output_in_game(text, 4);
    sex = INT.input_in_game_int();
    while (sex != 0 && sex != 1 && sex != 2) {
        text = "\nI don't believe you will make mistakes in such things. It's a joke, right?\n";
        INT.output_in_game(text, 2);
        sex = INT.input_in_game_int("Try again: ");
    }
    if (sex == 2)  sex = rand() % 2;
    text = "\nOf course you are a " + (string)(sex ? "[girl]" : "[boy]") + ". I mean, who will doubt that?\n\n";
    INT.output_in_game(text, 2);
}

void player::initVal(interface& INT) {
    string text = "Could you give a brief introduction on your academic achievements, "
                  "your personality and how willing you are to try new things?\n\n";
    INT.output_in_game(text, 4, true, true);
    text = "(Here you are going to input 3 integers a, b and c, and their sum "
           "a + b + c = 10. [a] represents your [academic intelligence], [b] represents "
           "your [charisma] and [c] represents your [courage].)\n\n";
           
    INT.output_in_game(text, 4);
    text = "(Be careful! Your allocation will influence your university life.)\n\n";
    INT.output_in_game(text, 3, false, false, false, true);
    while (true) {
        iq = INT.input_in_game_int("Academic intelligence (a): ");
        eq = INT.input_in_game_int("Charisma (b): ");
        courage = INT.input_in_game_int("Courage (c): ");
        if (iq < 0 || eq < 0 || courage < 0) {
            INT.output_in_game("Negative number? It's a joke of some kind, right?\n\n", 2);
            continue;
        }
        if (iq + eq + courage > 10) {
            INT.output_in_game("The sum of 3 numbers exceeds 10. Take your time, don't be too nervous.\n\n", 2);
        } else if (iq + eq + courage < 10) {
            INT.output_in_game("The sum of 3 numbers is below 10. Don't be so humble!\n\n", 2);
        } else {
            break;
        }
    }
}

void player::initSkill(interface& INT) {
    string text = "\nWhat else talents you want to specify?\n\n";
    INT.output_in_game(text, 4, true, true);
    text = "(You may choose at most 4 [talents] of yours. However, no one is perfect. " 
           "Every 2 [talents] may result in 1 random [shortcoming]. However, "
           "[shortcomings] could be overcome in the future.)\n\n";
    INT.output_in_game(text, 4);

    text = "(You grab your pen tightly, thinking...)\n\n";
    INT.output_in_game(text, 1, true, true, true, true);
    sleep(2);

    // This part should be randomized and objectivize
    text = "1. You come from a very rich family.\n   "
           "(Skill [Money talks]: Don't worry, you got money. A lot!)\n"
           "2. You are born with good luck.\n   "
           "(Skill [Luck is also strength]: You are more likely to success in some random events.)\n\n";
    string ski;
    INT.output_in_game(text);
    ski = INT.input_in_game_str();
    
    INT.output_in_game("!!!(This part needs further developing: Skills & Shortcomings needed!!!)\n\n");
}

void player::game_config(interface& INT, string& filename) {
    noecho();
    char c = wgetch(INT.get_gamewin());
    echo();
    if (c == 'c') {
        INT.save_interface(filename);
    }   
}

void player::printValue(interface& INT) {
    WINDOW* rht = INT.get_rhtwin();
    WINDOW* fa = INT.get_gamewin();
    wmove(rht, 1, 2);
    wclrtoeol(rht);
    wprintw(rht, "%s: week %d", month[mon].c_str(), ord);
    wmove(rht, 3, 2);
    wclrtoeol(rht);
    wprintw(rht, "IQ: %d", iq);
    wmove(rht, 4, 2);
    wclrtoeol(rht);
    wprintw(rht, "EQ: %d", eq);
    wmove(rht, 5, 2);
    wclrtoeol(rht);
    wprintw(rht, "Courage: %d", courage);
    wmove(rht, 6, 2);
    wclrtoeol(rht);
    wprintw(rht, "Luck: %d", luck);

    wmove(rht, 9, 2);
    wclrtoeol(rht);
    wprintw(rht, "Grades: %.2g", expectedGrades);
    wmove(rht, 10, 2);
    wclrtoeol(rht);
    wprintw(rht, "Pressure: %d", pressure);
    wmove(rht, 12, 2);
    wclrtoeol(rht);
    wprintw(rht, "Money: %d", money);
    box(rht, '+', '.');
    touchwin(fa);
    wrefresh(fa);
}

void player::printTranscript(interface& INT) {

    INT.output_in_game("\n");
    INT.output_in_game("+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++\n", 2, false);
//    sleep(1);
    INT.output_in_game("+     [the University of Hong Kong: Application form]     +\n", 2, false);
//    sleep(1);
    INT.output_in_game("+                                                         +\n", 2, false);
//    sleep(1);
    INT.output_in_game("+                                                         +\n", 2, false);
//    sleep(1);
    INT.output_in_game(name, 2, false, false, false, false, "+ Name: %-50s+\n");
//    sleep(1);
    INT.output_in_game("+                                                         +\n", 2, false);
//    sleep(1);
    INT.output_in_game((string)(sex ? "female" : "male"), 2, false, false, false, false, "+ Sex: %-51s+\n");
//    sleep(1);
    INT.output_in_game("+                                                         +\n", 2, false);
//    sleep(1);
    INT.output_in_game(to_string(iq), 2, false, false, false, false, "+ Academic talents: %-38s+\n");
//    sleep(1);
    INT.output_in_game(to_string(eq), 2, false, false, false, false, "+ Charisma: %-46s+\n");
//    sleep(1);
    INT.output_in_game(to_string(courage), 2, false, false, false, false, "+ Courage: %-47s+\n");
//    sleep(1);
    INT.output_in_game("+                                                         +\n", 2, false);
//    sleep(1);
    INT.output_in_game("+                                                         +\n", 2, false);
//    sleep(1);
    INT.output_in_game("+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++\n\n", 2, false);
}


const string landmark[10] = {"Victoria Peak", "Lantau Island", "Wong Tai Sin", "Science Park", 
                             "Sha Tin Racecourse", "Hong Kong Coliseum", "Causeway Bay"};

map<string, vector<item> > itemList;

void player::init(interface& INT) {
    initLandscape(INT);
    parttimeId.clear();
    unlockedLandmarks.clear();
    for (int i = 0; i < 10; ++i)    visited[i] = 0;
    viewYourGrades.clear();
    srand(time(0));
    std::string text = "\nAfter all these years of hard work, You've "
                       "finally got the chance to be admitted into HKU!\n\n"
                       "This is the school of your dream; you know you have to take the chance.\n\n"
                       "Now you are about to face your final challenge: completing the application"
                       " form.\n\n";
    INT.output_in_game(text);
    text = "(Your fingers are trembling with nervousness.)\n";
    INT.output_in_game(text, 1, true, true, true, true);
    text = "\n\n[the University of Hong Kong: Application form]\n\n";
    INT.output_in_game(text);


    initName(INT);
    initSex(INT);
    initVal(INT);
    money = 5000;
    pressure = 0;
    luck = 0;
    
    text = "Finished, finally!\n"
           "(You drop your pen, checking the application form carefully.)\n\n";
    INT.output_in_game(text, 1, true, true, true, true);

    while (true) {
        printTranscript(INT);
        sleep(2);
        text = "It seems perfect, except...\n\n";
        INT.output_in_game(text, 4, true, true);
        text = "1. Nuh, that's it. You are ready to submit it. \n"
               "2. There's a typo in the name and you want to change it. \n"
               "3. You realize you've written the wrong gender. Come on, seriously? \n"
               "4. You want to reallocate your talents, charisma and courage. \n";
        INT.output_in_game(text, 4, false);
        int op = INT.input_in_game_int();
        while (op < 1 || op > 4)
            op = INT.input_in_game_int("Invalid input. Your prompt here: ");
        if (op == 1) {
            text = "\n(Submitted succesfully. You let out a deep sigh and wait for the results with hope.)\n\n";
            INT.output_in_game(text, 1, true, true, true, true);
            break;
        } else if (op == 2) {
            INT.output_in_game("\n\n");
            initName(INT);
        } else if (op == 3) {
            INT.output_in_game("\n\n");
            initSex(INT);
        } else if (op == 4) {
            INT.output_in_game("\n\n");
            initVal(INT);
        } 
    }
    
   getch();    
}



// ITEMS_INTERACTION_MODULE

void player::encounterItems(item it, interface& INT, bool reading) {
    string text = "\nCurrent activity: " + it.getName() + "\n";
    INT.output_in_game(text, 2);
    INT.output_in_game(it.description(), 1);
    iq += it.addiq();
    eq += it.addeq();
    courage += it.addcourage();
    luck += it.addluck();
    money -= it.getCost();
    if (it.addskill() > 0)
        specialSkill[it.addskill()] = 1;
    if (it.addskill() < 0)
        specialSkill[-it.addskill()] = 0;
    printValue(INT);
    INT.output_in_game(it.positiveEffect(), 2);
    INT.output_in_game(it.negativeEffect(), 3);
    if (it.addiq() > 0 && reading) {
        INT.output_in_game("\n(Reading week bonus: IQ improves more than ordinary week)\n", 2);
        INT.output_in_game("[IQ ++]\n", 2);
        iq++;
    }
    if (it.addeq() > 0 && reading) {
        INT.output_in_game("\n(Reading week bonus: EQ improves more than ordinary week)\n", 2);
        INT.output_in_game("[EQ ++]\n", 2);
        eq++;
    }
    if (it.addcourage() > 0 && reading) {
        INT.output_in_game("\n(Reading week bonus: Courage improves more than ordinary week)\n", 2);
        INT.output_in_game("[Courage ++]\n", 2);
        courage++;
    }
    if (it.addluck() > 0 && reading) {
        INT.output_in_game("\n(Reading week bonus: Luck improves more than ordinary week)\n", 2);
        INT.output_in_game("[Luck ++]\n", 2);
        luck++;
    }
    printValue(INT);
}

// STUDY_MODULE

        // add weather prompt, random advice prompt!!!

string player::study_prompt() {
    if (expectedGrades < 3)
        return "(Your expected grade is below 3. Maybe focusing on study is a better choice?)\n";
    if (expectedGrades > 4)
        return "(Wow...you really do love studying!)\n";
    if (expectedGrades > 3.7)
        return "(It seems your expected grade is satisfactory. Still want to improve?)\n";
    return "(It's always a good choice to spend time on study, is it?)\n";
}

string player::doelse_prompt() {  // ADVICE!!!
    if (pressure >= 10)
        return "(You are under too much stress! Maybe you should do something else to change your mood.)\n";
    return "(University is NOT all about study. Let's see what else you can do!)\n";
}

string act[3] = {"watched a popular TV series!\n", 
                 "played a video game for a while!\n", 
                 "watched a famous movie!\n"};

// SURF_THE_INTERNET_MODULE

bool player::search_for_rd(int rd) {
    for (int i = 0; i < parttimeId.size(); ++i)
        if (parttimeId[i] == rd) { return true; }
    return false;
}

void player::surf_the_internet(interface& INT, bool reading) {        // news module could be created
    srand(time(0));
    INT.output_in_game("You " + act[rand() % 3], 2);
    INT.output_in_game("[pressure --]", 2);
    pressure -= 3;
    if (reading) {
        INT.output_in_game("\n(Reading week bonus: pressure decreases more than ordinary week)\n", 2);
        INT.output_in_game("[pressure -]", 2);
        pressure--;
    }
    if (pressure < 0)   pressure = 0;
    printValue(INT);
    int rd = rand() % 2, sz = unlockedLandmarks.size();
    if (rd == 1 && sz != 0) {
        rd = rand() % sz;
        
        if (search_for_rd(rd)) rd = (rd + 1) % sz;
        if (search_for_rd(rd)) rd = (rd + 1) % sz;
        if (!search_for_rd(rd)) {
            INT.output_in_game("\n\nNew email!\n", 2);
            INT.output_in_game("\nYou've received a part-time job offer from a company in " + unlockedLandmarks[rd] + " !\n", 2);
            string text = "\n(A new part-time job unlocked! " 
                          "Your ability improves the same as [visiting] the place when "
                          "[doing part-time job] there.)\n\n";
            INT.output_in_game(text, 3, true, false, false, true);
            parttimeId.push_back(rd);
        }
    }
}

// EXPLORE_LANDMARKS_MODULE

void player::initLandscape(interface& INT) {  // cost, iq, eq, courage, luck, skill, name, des
    itemList.clear();
    for (int i = 0; i < 10; ++i)    visited[i] = 0;
    string des = "\n(Enjoy the beautiful night city view from the top of the Peak!"
                 " Hiking alone in the mountain may improve your [courage]...)\n";
    itemList["Victoria Peak"].push_back(item(0, 0, 0, 1, 0, 0, "[hiking]", des));
    des = "\n(The Great Buddha looks at the world calmly, without sorrow or joy. "
          "You seem to have gained some enlightenment...)\n";
    itemList["Lantau Island"].push_back(item(0, 0, 1, 0, 0, 0, "[Visiting the Po Lin Monastery]", des));
    des = "\n(TAO gives birth to one, one to two, two to three, and three to everything..."
          "The gods have heard your prayers...)\n";
    itemList["Wong Tai Sin"].push_back(item(0, 0, 0, 0, 1, 0, "[Visiting Wong Tai Sin Temple]", des));
    des = "\n(Here is the center of cutting-edge technology in Hong Kong! "
          "Your [intelligence] may be improved here...)\n";
    itemList["Science Park"].push_back(item(0, 1, 0, 0, 0, 0, "[Visiting HKSTP]", des));
    des = "\n(Driven by the atmosphere, you've placed a high bet on a beautiful horse! "
          "It's NOT a [wise] choice, but sometimes you just want to go crazy!!!)\n";
    itemList["Sha Tin Racecourse"].push_back(item(1500, -1, 0, 2, 0, 0, "[Joining in horse racing]", des));
    itemList["Sha Tin Racecourse"].push_back(item(0, 0, 0, 0, 0, 0, "NULL", "Cannot part-time here"));
    des = "\n(HK Coliseum in Hung Hom is a jewel of Hong Kong pop culture. "
          "The singer's wonderful performance seems to teach you what [charm] is all about)\n";
    itemList["Hong Kong Coliseum"].push_back(item(1000, 0, 2, 0, 0, 0, "[Watching a concert]", des));
    des = "\n(Causeway Bay is a famous shopping area in Hong Kong. "
          "Maybe you could find something useful there? )\n";
    itemList["Causeway Bay"].push_back(item(0, 0, 0, 0, 0, 0, "[Shopping]", des));
    des = "\n   (Shopping in stationary store: may improve your study efficiency? [IQ] )\n";
    itemList["Causeway Bay"].push_back(item(3000, 5, 0, 0, 0, 0, "[Shopping in the stationary store]", des));
    des = "\n   (Shopping in clothing store: may improve your charisma? [EQ] )\n";
    itemList["Causeway Bay"].push_back(item(3000, 0, 5, 0, 0, 0, "[Shopping in the clothing store]", des));
    des = "\n   (A new horror movie is being screened in the cinema. Take a challenge! [Courage])\n";
    itemList["Causeway Bay"].push_back(item(3000, 0, 0, 5, 0, 0, "[Watching a horror movie in cinema]", des));
    des = "\n   (Mystic Stone Store? Looks pretty suspicious, should we try it?)\n";
    itemList["Causeway Bay"].push_back(item(3000, 0, 0, 0, 5, 0, "[Buying a mystic stone]", des));

    for (int rd = 0; rd < 8; ++rd) {
        if (itemList[landmark[rd]].size() == 1) {
            item visit = itemList[landmark[rd]][0];
            item part_time(-1000, visit.addiq(), visit.addeq(), visit.addcourage(), 
                            visit.addluck(), 0, "[Doing part-time job]", visit.description());
            itemList[landmark[rd]].push_back(part_time);
        }
    }
}

void player::horseracing(interface& INT) {
    srand(time(0));
    int rd = rand() % 10 + 1;

    INT.output_in_game("\nWhich horse you think will run the fastest?\n", 4, true, true);
    INT.output_in_game("(Please enter a number between 1 - 10)\n", 4, false);

    int op = INT.input_in_game_int("A number between 1 - 10: ");
    while (op < 1 || op > 10)
        op = INT.input_in_game_int("Invalid input! please enter a number between 1 - 10: ");
    if (luck > 10) {
        INT.output_in_game("\nYour are extremely lucky (luck > 10)! You could always bet on the winning horse!\n", 2);
        INT.output_in_game("\nYou earned quite a bonus! \n[Money ++]\n\n", 2);
        money += 3000;
    } else {
        INT.output_in_game("\nThe winning horse number is [" + to_string(rd) + "] !\n");
        if (rd == op) {
            INT.output_in_game("\nYou earned quite a bonus! \n[Money ++]\n\n", 2);
            money += 3000;
        } else {
            INT.output_in_game("\n Hmmmm...You are obviously not an expert on this. You may improve your [luck] and try next time!\n", 1);
        }
    }
}

void player::shopping(interface& INT, string place, bool reading) {
    INT.output_in_game("What kind of stores do you want to go to?\n", 4, true, true);
    if (money < 3000) {
        INT.output_in_game("\nIt seems that you don't have enough money (3000 at least)\n", 3);
        INT.output_in_game("\nYou go for a window shopping. [Pressure] decreases.\n", 2);
        INT.output_in_game("[pressure --]\n", 2);
        pressure--;

    } else {
        string text = "\n1. Stationary store" + itemList[place][1].description() + ""
                      "2. Clothing store" +  itemList[place][2].description() + ""
                      "3. Cinema" + itemList[place][3].description() + ""
                      "4. Mystic stone store" + itemList[place][4].description() + "";
        INT.output_in_game(text, 4, false);
        int op = INT.input_in_game_int("Please enter the store number: ");
        while (op < 1 || op > 4)
            op = INT.input_in_game_int("Invalid input, try again: ");
        encounterItems(itemList[place][op], INT, reading);
    }
}

void player::explore_the_place(interface& INT, string place, bool reading) {
    int id;
    for (int i = 0; i < 7; ++i) {
        if (place == landmark[i]) {
            id = i;
            break;
        }
    }
    switch (id) {
        case 0:
        case 1:
        case 2:
        case 3:
        case 5:
            encounterItems(itemList[place][0], INT, reading);
            break;
        case 4:
            encounterItems(itemList[place][0], INT, reading);
            horseracing(INT);
            break;
        case 6:
            encounterItems(itemList[place][0], INT, reading);
            shopping(INT, place, reading);
            break;
    }
}

void player::go_somewhere_else(interface& INT, bool reading) {
    string text;
    INT.output_in_game("\nWhere do you want to go?\n", 4, true, true);
    INT.output_in_game("\n1. Below are the places you've already explored...\n", 4, false);
    if (unlockedLandmarks.empty()) {
        INT.output_in_game("   Seems you haven't found any interesting place yet.\n", 7, false);
    } else {
        for (int i = 0; i < unlockedLandmarks.size(); ++i)
            INT.output_in_game("   " + unlockedLandmarks[i] + "\n", 7, false);
    }
    INT.output_in_game("\n2. Just wandering in the city... (may find some interesting place?)\n", 4, false);
    int op;
    if (unlockedLandmarks.empty()) {
        op = INT.input_in_game_int("You haven't found any specific destination now. Try to explore the city randomly...: ");
        while (op != 2)
            op = INT.input_in_game_int("Try enter 2! Trust me! ");
    } else {
        op = INT.input_in_game_int();
        while (op != 1 && op != 2)
            op = INT.input_in_game_int("Invalid input. Try again: ");
    }
    if (op == 1) {
        INT.output_in_game("\n You could visit the place that you've previously explored...\n\n", 4, true, true);
        for (int i = 0; i < unlockedLandmarks.size(); ++i) {
            INT.output_in_game(to_string(i + 1) + ". ", 7, false);
            INT.output_in_game(unlockedLandmarks[i] + "\n", 7, false);
        }
        int destination = INT.input_in_game_int("Where you want to go? (enter the number id): ");
        
        while (destination < 1 || destination > unlockedLandmarks.size()) {
            destination = INT.input_in_game_int("Invalid input. Please enter the correct number id: ");
        }
        explore_the_place(INT, unlockedLandmarks[destination - 1], reading);
    } else {
        srand(time(0));
        int ex = rand() % 7;
        if (unlockedLandmarks.size() < 7) { // take care 
            while (visited[ex])
                ex = rand() % 7;
            INT.output_in_game("\nYou've found a new place --- [" + landmark[ex] + "]!\n\n", 2);
            visited[ex] = 1;
            unlockedLandmarks.push_back(landmark[ex]);
        } 
        explore_the_place(INT, landmark[ex], reading);
    }
    INT.output_in_game("\nGoing out reduces your pressure...\n", 2);
    INT.output_in_game("[pressure --]\n", 2);
    pressure--;
    if (pressure < 0)   pressure = 0;
    printValue(INT);
}

// PART_TIME MODULE

bool player::do_part_time(interface& INT, bool reading) {
    int sz = parttimeId.size();
    if (sz == 0) {
        string text = "\n(You haven't received any job offer currently. Try visiting "
                      "some places or surfing the internet for some information.)\n\n";
        INT.output_in_game(text, 3, true, false, false, true);
        return false;
    } else {
        srand(time(0));
        int rd = rand() % sz;
        string text = "\nYou check the calender, and find that today you could do part-time job in " + unlockedLandmarks[parttimeId[rd]] + ".\n\n";
        INT.output_in_game(text, 1);
        encounterItems(itemList[unlockedLandmarks[parttimeId[rd]]][1], INT, reading);
        // money system
    }
    return true;
}

void player::simulate_ordinary_week(interface& INT, int _ord, int _mon, bool reading, bool revision) {
    ord = _ord, mon = _mon;
    INT.clearwin_in_game();
    printValue(INT);

    string text = "It's the " + order[ord] + " week in " + month[mon] + ".\n\n";
    INT.output_in_game(text, 7, false);

    if (revision) {
        text = "It's a [revision week] --- It's the last week before final assessment period!\n"
               "(During this week, studying will [improve grades more])\n";
    } else if (reading) {
        text = "It's a [reading week] --- You are free to schedule all the time of this week!\n"
               "(During this week, the effects of all your actions will be [enhanced])\n";
    } else {
        text = "It's an ordinary teaching week --- attending the courses improves your expected grades!\n"
               "[grades +]\n";
        expectedGrades += 0.1;
        printValue(INT);
    }

    INT.output_in_game(text, 2);
}

void player::simulate_action(interface& INT, bool reading, bool revision) {

    string text;
    do {
        INT.output_in_game("\n So, What's your plan?\n\n", 4, true, true);
        text = "1. Spend all your spare time in main library / Chi Wah learning common.\n"
                "   " + study_prompt(); 
        INT.output_in_game(text, 4, false);
        text =  "\n2. Go somewhere else.\n"
                "   (Explore new place! Meet new people!)\n\n"
                "3. Spend the time on the Internet.\n"
                "   (Keep browsing until you're bored...that's not likely to happen.)\n\n"
                "4. Do part-time jobs.\n"
                "   (Money and experience. Kill two birds with one stone.)\n\n";
        INT.output_in_game(text, 4, false);

        int op = INT.input_in_game_int();
        while (op != 1 && op != 2 && op != 3 && op != 4)  
            op = INT.input_in_game_int("Invalid input: try again: ");
        if (op == 1) {
            text = "\nSpent a fufilling time at the main library...\n"
                    "[grades +++]\n"
                    "[pressure +]\n";
            expectedGrades += 0.15 * (1.0 + iq / 10.0) * (1.0 - pressure / 20.0);
            pressure += 1;
            if (reading) {
                INT.output_in_game("\n(Reading week bonus: grades improve more than ordinary week)\n", 2);
                INT.output_in_game("[Grades +]\n", 2);
                expectedGrades += 0.15 * (1.0 + iq / 10.0) * (1.0 - pressure / 20.0);
            }
            if (revision) {
                INT.output_in_game("\n(Revision week bonus: grades improve more than ordinary week)\n", 2);
                INT.output_in_game("[Grades +++]\n", 2);
                expectedGrades += 0.1;
            }
            printValue(INT);
            INT.output_in_game(text, 2);
            break;
        }
        if (op == 2) {
            go_somewhere_else(INT, reading);
            break;
        }
        if (op == 3) {
            surf_the_internet(INT, reading);
            break;
        }
        if (op == 4) {
            if (do_part_time(INT, reading)) {
                break;
            }   
        }
    } while (true);

    if (money < 0) {
        text = "\n\nYou spend so much money that you don't have enough to live on...\n"
               "(have to ask parents for assistance...)\n\n";
        INT.output_in_game(text, 4);
        text = "[Money ++++]\n";
        INT.output_in_game(text, 2);
        text = "[Charisma / EQ --]\n\n";
        INT.output_in_game(text, 3, true, false, false, true);
        money += 1000;
        eq -= 1;
        printValue(INT);
    }
}

/* 
there are about 15 weeks in the first semester: here is the outline

5 ordinary weeks (SEP-OCT 9th)
1 reading week (OCT 10th-17th)
6 ordinary weeks (OCT 18th-NOV 30th)
1 week: revision period (DEC 1st-7th)
2 week: assessment period (DEC 8th-23rd)

Special Dates:
National Day (OCT 1st)
Double Ninth Festival (OCT 4th)
*/

void player::simulate_semester_begin() {
    expectedGrades = 0;
}

string player::grade_converter(double x) {
    if (x >= 4.3)      { return "A+"; }
    else if (x >= 4)   { return "A"; }
    else if (x >= 3.6) { return "A-"; }
    else if (x >= 3.3) { return "B+"; }
    else if (x >= 3)   { return "B"; }
    else if (x >= 2.6) { return "B-"; }
    else if (x >= 2.3) { return "C+"; }
    else if (x >= 2.0) { return "C"; }
    else if (x >= 1.6) { return "C-"; }
    else { return "D"; }
}

void player::simulate_assessment_period(interface& INT) {
    INT.clearwin_in_game();
    ord += 1;
    printValue(INT);
    string text = "It's the final [assessment period] of this semester!\n"
                  "It's time to test what you've learnt this semester...\n\n";
    INT.output_in_game(text, 2);
    text = "Your intelligence / IQ is: " + to_string(iq) + "\n\n"
           "Your luck is: " + to_string(luck) + "\n\n";
    INT.output_in_game(text, 1, true, false, false, true);
    expectedGrades *= (iq / 40 + 1.0);
    if (luck >= 10) {
        text = "\nYour excessive luck makes you even can guess the right answers!\n"
               "[grades +++]\n\n";
        INT.output_in_game(text, 2);
        expectedGrades += 0.5;
    }
    printValue(INT);
    string GRADE;
    if (expectedGrades >= 4.3)      { GRADE = "A+", viewYourGrades.push_back(4.3); }
    else if (expectedGrades >= 4)   { GRADE = "A", viewYourGrades.push_back(4); }
    else if (expectedGrades >= 3.6) { GRADE = "A-", viewYourGrades.push_back(3.6); }
    else if (expectedGrades >= 3.3) { GRADE = "B+", viewYourGrades.push_back(3.3); }
    else if (expectedGrades >= 3)   { GRADE = "B", viewYourGrades.push_back(3); }
    else if (expectedGrades >= 2.6) { GRADE = "B-", viewYourGrades.push_back(2.6); }
    else if (expectedGrades >= 2.3) { GRADE = "C+", viewYourGrades.push_back(2.3); }
    else if (expectedGrades >= 2.0) { GRADE = "C", viewYourGrades.push_back(2); }
    else if (expectedGrades >= 1.6) { GRADE = "C-", viewYourGrades.push_back(1.6); }
    else { GRADE = "D", viewYourGrades.push_back(1.5); }

    text = "Your final letter grade of this semester is...\n\n";
    INT.output_in_game(text, 1, true, false, false, true);
    sleep(2);
    INT.output_in_game(GRADE + "!\n\n", 1, true, false, false, true);
    getch();
}

void player::simulate_semester_end(interface& INT, int sch, int dep, int* mainProcess, int vacation) {
    
    if (vacation != 0) simulate_assessment_period(INT);
    INT.clearwin_in_game();
    mon += 1, ord = 1;
    if (mon == 13)  mon = 1;
    printValue(INT);

    if (vacation != 0) {
        string vac = (vacation == 1) ? "Winter" : "Summer";
        string text = "It's the [" + vac + " vacation] !\n"
                      "Relax well or continue to improve yourself, it's up to you!\n\n";
        INT.output_in_game(text, 2);
        text = "(Vacation will last for quite a long time: It's a great time to overcome "
               "your shortnesses! Make appropriate choices to balance your abilities...)\n\n";
        INT.output_in_game(text, 3, true, false, false, true);

        if (sch == 1) {
            INT.output_in_game("\nNew email!\n", 2);
            INT.output_in_game("\nThe result of the scholarship project that you previously applied has released!\n\n", 2);
            if (viewYourGrades.back() >= 2.3) {
                string text = "Your achievements have impressed the funders deeply!\n"
                              "[Money +++]\n\n";
                INT.output_in_game(text, 2);
                money += 5000;
                printValue(INT);
            } else {
                string text = "Unfortunately, you haven't been chosen...\n\n";
                INT.output_in_game(text, 2);
                text = "(Improve your grades or participate in more activities and try to apply next time!)\n\n";
                INT.output_in_game(text, 3, true, false, false, true);
            }
        }
        if (dep == 1 && pressure >= 10) {
            string text = "\nExcessive anxiety overwhelms you...\n"
                          "You start to feel disinterested in everything...\n\n";
            INT.output_in_game(text, 1, true, false, true);
            text = "You've built up too much pressure! ([pressure >= 10])\n"
                   "[Suffer from depression]\n\n";
            INT.output_in_game(text, 3, true, false, false, true);
            text = "This vacation, You are taken by your parents to a specialist psychiatric facility for treatment...\n"
                   "[Pressure ------]\n\n";
            INT.output_in_game(text, 2);
            pressure = 0;
            printValue(INT);
            return;
        }
        if (mainProcess[0] == 1) {
            INT.output_in_game("\nNew email!\n", 2);
            INT.output_in_game("\nThe result of the studying abroad project that you previously applied has released!\n\n", 2);
            if (viewYourGrades.back() >= 2 && money >= 8000) {
                INT.output_in_game("\nSeems you are eligible for this project and have prepared enough money!!\n", 2);
                string text = "\nDo you want to study abroad in this vacation? (This will cost you money 8000 $)\n";
                INT.output_in_game(text, 4, true, true);
                text = "\n1. Of course! It's always a good chance to exprience a different culture.\n"
                       "2. Nah, I have other plan afterwards.\n\n";
                INT.output_in_game(text, 4, false);
                int op = INT.input_in_game_int("Enter your choice: ");
                while (op != 1 && op != 2)  op = INT.input_in_game_int("Invalid input. Try again: ");
                if (op == 1) {
                    text = "Attended the " + vac + " courses at an overseas university!\n"
                           "Learnt a lot and experienced a different culture...\n\n"
                           "[Intelligence / IQ ++++]\n"
                           "[Charisma / EQ ++++]\n\n";
                    INT.output_in_game(text, 2);
                    iq += 4, eq += 4;
                    text = "[Money ----]\n\n";
                    money -= 8000;
                    INT.output_in_game(text, 3, true, false, false, true);\
                    printValue(INT);
                    mainProcess[0] = 3;
                    return;
                } 
            } else {
                string text = "Unfortunately, it seems you are not eligible for this project right now...\n\n";
                INT.output_in_game(text, 2);
                text = "(Improve your grades and earn enough money (8000 $ at least), then try to apply next time!)\n\n";
                INT.output_in_game(text, 3, true, false, false, true);
                mainProcess[0] = 0;
            }
        }

        if (mainProcess[1] == 1) {
            INT.output_in_game("\nNew email!\n", 2);
            INT.output_in_game("\nThe result of the short-term internship project that you previously applied has released!\n", 2);
            if (viewYourGrades.back() >= 3) {
                INT.output_in_game("\nSeems you are eligible for this project!!\n", 2);
                string text = "\nDo you want work as intern in this vacation?\n";
                INT.output_in_game(text, 4, true, true);
                text = "\n1. Of course! It will be an invaluable experience before I actually get to work.\n"
                       "2. Nah, I have other plan afterwards.\n\n";
                INT.output_in_game(text, 4, false);
                int op = INT.input_in_game_int("Enter your choice: ");
                while (op != 1 && op != 2)  op = INT.input_in_game_int("Invalid input. Try again: ");
                if (op == 1) {
                    text = "Doing the internship in a famous company!\n"
                           "Gained work experience and learnt how to collaborate with others...\n\n"
                           "[Money +++]\n"
                           "[Courage ++++]\n"
                           "[Charisma / EQ ++++]\n\n";
                    INT.output_in_game(text, 2);
                    courage += 4, eq += 4;
                    money += 6000;
                    printValue(INT);
                    mainProcess[1] = 3;
                    return;
                } 
            } else {
                string text = "Unfortunately, it seems you are not eligible for this project right now...\n\n";
                INT.output_in_game(text, 2);
                text = "(Improve your grades or participate in more activities, then try to apply next time!)\n\n";
                INT.output_in_game(text, 3, true, false, false, true);
                mainProcess[1] = 0;
            }
        }

        do {
            INT.output_in_game("\n So, What's your plan?\n\n", 4, true, true);
            text = "1. Sign up for HKU " + vac + " programmes.\n"
                    "   (It's always not a bad choice to earn some extra credits...)\n\n"
                    "2. Go Travelling!\n"
                    "   (Even if it sounds clichéd, travel is always desirable)\n\n"
                    "3. Stay at home. Do nothing.\n"
                    "   (A true sense of rest...you really want to do that? )\n\n"
                    "(Other activities may be unlocked with your improved abilities...)\n\n";

            INT.output_in_game(text, 4, false);

            int op = INT.input_in_game_int();
            while (op != 1 && op != 2 && op != 3)  
                op = INT.input_in_game_int("Invalid input: try again: ");
            if (op == 1) {
                text = "\nSpent a fufilling time at HKU...\n"
                        "Fulfilling though, It didn't seem like much of a vacation...\n"
                        "[IQ +++]\n"
                        "[pressure +]\n\n";
                INT.output_in_game(text, 2);
                iq += 4;
                pressure += 2;
                printValue(INT);
                break;
            }
            if (op == 2) {
                if (money >= 2000) {
                    string s = (sex == 0) ? "girl" : "boy";
                    text = "\nGo travelling with your... ";
                    if (mainProcess[3] >= 2)    text += s;
                    text += "friend!\n";
                    INT.output_in_game(text, 2);
                    text = "Exploring a whole new place widens your horizons!\n"
                           "[Pressure --]\n"
                           "[Charisma / EQ] ++\n\n";
                    INT.output_in_game(text, 2);
                    text = "[Money --]\n\n";
                    INT.output_in_game(text, 3, true, false, false, true);
                    money -= 2000;
                    pressure -= 4;
                    if (pressure < 0)   pressure = 0;
                    eq += 4;
                    printValue(INT);
                    break;
                } else {
                    text = "\n(You cannot even afford a travel right now..."
                           "Try to earn more money! (2000 $ at least)\n";
                    INT.output_in_game(text, 3, true, false, false, true);
                }
            }   
            if (op == 3) {
                text = "\nReally? This is how you spend your holidays?\n"
                        "Okay, I admit I'm a little envious of this lifestyle...\n"
                        "[Pressure -> 0]\n"
                        "[Luck ++++]\n\n";
                INT.output_in_game(text, 2);
                text = "[Intelligence / IQ -]\n"
                       "[Charisma / EQ -]\n"
                       "[Courage -]\n\n";
                INT.output_in_game(text, 3, true, false, false, true);
                pressure = 0;
                courage --;
                eq--;
                iq--;
                luck += 4;
                printValue(INT);
                break;
            }
        } while (true);
        
        if (mainProcess[0] == 4)
            mainProcess[0] = 0;
        if (mainProcess[1] == 4)
            mainProcess[1] = 0;
    } else {
        string text = "At the end of four years, you have your graduation ceremony.\n"
                      "You are going to leave this picturesque campus and you miss it very much.\n"
                      "You begin to reflect on these four years of growth ------\n\n";
        INT.output_in_game(text, 3);

        text = "Intelligence: " + to_string(iq) + "\n"
               "Charisma: " + to_string(eq) + "\n"
               "Courage: " + to_string(courage) + "\n"
               "Luck: " + to_string(luck) + "\n\n"
               "University life not only increases your knowledge, "
               "but also makes you more courageous and better at getting along with people.\n\n";
        INT.output_in_game(text, 1, true, false, false, true);

        text = "You've explored the Hong Kong city, and these places leave a lasting impression on you...\n\n";
        INT.output_in_game(text, 3, true, false, false, true);
        for (int i = 0; i < unlockedLandmarks.size(); ++i)
            INT.output_in_game(unlockedLandmarks[i] + "\n", 3, true, false, false, true);
        
        text = "\nYou continue to make progress in the face of academic challenges...\n"
               "Here's your academic transcript for four years ---\n\n";
        INT.output_in_game(text, 6, true, false, false, true);
        double tot = 0;
        for (int i = 0; i < viewYourGrades.size(); ++i) {
            INT.output_in_game("The " + to_string(i + 1) + "-th semester: " + grade_converter(viewYourGrades[i]) + "\n", 6, true, false, false, true);
            tot += viewYourGrades[i];
        }
        tot /= 8;
        INT.output_in_game("The final letter grade of yours is: " + grade_converter(tot) + " !\n", 6, true, false, false, true);
        if (tot >= 3.6) {
            INT.output_in_game("You've got the [HKU first honor] !\n\n", 6, true, false, false, true);
        }

        text = "In these four years, you have achieved many things, and they"
               "have shaped your future...\n\n";
        INT.output_in_game(text, 4);
        sleep(1);
        if (mainProcess[0] == 3) {
            text = "You have studied abroad on exchange and learned about a different culture.\n\n"
                   "(This experience enables you to further studying for a PhD abroad)\n\n";
        } else {
            text = "(failed to complete the challenge: study abroad)\n\n"
                   "Having the experience of an exchange abroad proved to be very helpful later on. "
                   "However, life is not all smooth sailing. \n\n";
        }
        INT.output_in_game(text, 5, true, false, false, true);
        sleep(2);
        if (mainProcess[1] == 3) {
            text = "You have participated in many interships and have gained considerable work experience.\n\n"
                   "(During the subsequent job search, your fantastic CV impressed many companies.)\n\n";
        } else {
            text = "(failed to complete the challenge: internship)\n\n"
                   "You didn't have an internship during your time at university, which made you "
                   "quite uncomfortable when you first started working. However, you soon learn how to balance work and life. \n\n";
        }
        INT.output_in_game(text, 1, true, false, false, true);
        sleep(2);
        if (mainProcess[2] == 3) {
            text = "You were the leader of a club at university and this has developed your strong leadership skills.\n\n"
                   "(In later years, you have the opportunity to join the political arena and dedicate yourself to the betterment of society)\n\n";
        } else if (mainProcess[2] == 2) {
            text = "(failed to complete the challenge: leader of the club)\n\n"
                   "You have learned to work together by joining clubs and participating in interesting activities during your time at university. \n\n";
        } else {
            text = "(failed to complete the challenge: joining a club)\n\n"
                   "The disadvantages of university societies are obvious: the social purpose far outweighs the interest purpose."
                   "Therefore, you've never taken an interest in them.\n\n";
        }
        INT.output_in_game(text, 2);
        sleep(2);
        if (mainProcess[3] == 3) {
            text = "You managed to find someone to love at university and stay with him/her for the rest of your life.\n\n";
        } else if (mainProcess[2] == 2) {
            text = "(failed to complete the challenge: maintaining relationship)\n\n"
                   "Your relationship at university ended in a break-up. This makes you depressed for a long time, but in the end you realise that it was also a precious memory.\n\n";
        } else {
            text = "(failed to complete the challenge: Dating someone)\n\n"
                   "You have remained single throughout your university career. This is a very great achievement!\n\n";
        }
        INT.output_in_game(text, 3, true, false, false, true);
        sleep(2);
        if (mainProcess[4] == 3) {
            text = "Your capstone project has impressed a business man deeply and several years later you become the chief designer in his company.\n\n";
        } else {
            text = "(failed to complete the challenge: completing capstone)\n\n"
                   "Your capstone project was completed very haphazardly. This at one point made you feel very regretful and missed the opportunity to be known.\n\n";
        }
        if (mainProcess[5] == 3) {
            text = "You have chosen a minor. On your capstone project show, your integrated skills "
                   "surprised a lot of visitors, and therefore you receive many offers from famous companies.\n\n";
        } else {
            text = "(failed to complete the challenge: choosing minor)\n\n"
                   "You are very specialised in your field. Sometimes, however, you may find that knowledge in other areas is also quite useful.\n\n";
        }
        INT.output_in_game(text, 6, true, false, false, true);
        sleep(2);

        text = "Congratulations on getting through the game! Due to time constraints, many of the features that were intended to be implemented had to be discarded...\n"
               "However the process of making this game has taught us a lot. That's the best part of this task.\n\n";
        INT.output_in_game(text);
    }    
}

