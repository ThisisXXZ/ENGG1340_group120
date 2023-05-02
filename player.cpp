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

int player::getIq() const {
    return iq;
}

int player::getEq() const {
    return eq;
}

double player::getGPA() const {
    return gpa;
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
    INT.output_in_game("+ Skills (needs developing...)                            +\n", 2, false);
//    sleep(1);
    INT.output_in_game("+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++\n\n", 2, false);
}

vector<int> parttimeId;
const string landmark[10] = {"Victoria Peak", "Lantau Island", "Wong Tai Sin", "Science Park", 
                             "Sha Tin Racecourse", "Hong Kong Coliseum", "Causeway Bay"};
vector<string> unlockedLandmarks;
map<string, vector<item> > itemList;
bool visited[10];

void player::init(interface& INT) {
    initLandscape(INT);
    parttimeId.clear();
    srand(time(0));
    std::string text = "\nAfter all these years of hard work, You've "
                       "finally got the chance to be admitted into HKU!\n\n"
                       "This is the school of your dream; you know you have to take the chance.\n\n"
                       "Now you are about to face your final challenge: completing the application"
                       " form.\n\n";
    INT.output_in_game(text);
    text = "(Your fingers are trembling with nervousness.)\n";
    INT.output_in_game(text, 1, true, true, true, true);
    sleep(2);
    text = "\n\n[the University of Hong Kong: Application form]\n\n";
    INT.output_in_game(text);


    initName(INT);
    initSex(INT);
    initVal(INT);
    initSkill(INT);
    money = 3000;
    
    text = "Finished, finally!\n"
           "(You drop your pen, checking the application form carefully.)\n\n";
    INT.output_in_game(text, 1, true, true, true, true);

    while (true) {
        printTranscript(INT);

        text = "It seems perfect, except...\n\n";
        INT.output_in_game(text, 4, true, true);
        text = "1. Nuh, that's it. You are ready to submit it. \n"
               "2. There's a typo in the name and you want to change it. \n"
               "3. You realize you've written the wrong gender. Come on, seriously? \n"
               "4. You want to reallocate your talents, charisma and courage. \n"
               "5. You want to modify your skills. \n\n";
        INT.output_in_game(text, 4, false);
        int op = INT.input_in_game_int();
        while (op < 1 || op > 5)
            op = INT.input_in_game_int("Invalid input. Your prompt here: ");
        if (op == 1) {
            text = "\n(Submitted succesfully. You let out a deep sigh and wait for the results with hope.)\n\n";
            INT.output_in_game(text, 1, true, true, true, true);
            sleep(2);
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
        } else if (op == 5) {
            INT.output_in_game("\n\n");
            initSkill(INT);
        }

    }
    
   getch();     // 过场动画?
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

void player::surf_the_internet(interface& INT, bool reading) {        // news module could be created
    srand(time(0));
    INT.output_in_game("You " + act[rand() % 3], 2);
    INT.output_in_game("[pressure --]", 2);
    pressure -= 2;
    if (reading) {
        INT.output_in_game("\n(Reading week bonus: pressure decreases more than ordinary week)\n", 2);
        INT.output_in_game("[pressure -]", 2);
        pressure--;
    }
    if (pressure < 0)   pressure = 0;
    int rd = rand() % 2, sz = unlockedLandmarks.size();
    if (rd == 1 && sz != 0) {
        rd = rand() % sz;
        if (itemList[unlockedLandmarks[rd]].size() != 1) rd = (rd + 1) % sz;
        if (itemList[unlockedLandmarks[rd]].size() != 1) rd = (rd + 1) % sz;
        if (itemList[unlockedLandmarks[rd]].size() == 1) {
            INT.output_in_game("\n\nNew email!\n", 2);
            INT.output_in_game("\nYou've received a part-time job offer from a company in " + unlockedLandmarks[rd] + " !\n", 2);
            string text = "\n(A new part-time job unlocked! " 
                          "Your ability improves the same as [visiting] the place when "
                          "[doing part-time job] there.)\n\n";
            INT.output_in_game(text, 3, false, false, false, true);
            item visit = itemList[unlockedLandmarks[rd]][0];
            item part_time(-1000, visit.addiq(), visit.addeq(), visit.addcourage(), 
                            visit.addluck(), 0, "[Doing part-time job]", visit.description());
            itemList[unlockedLandmarks[rd]].push_back(part_time);
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
}

void player::horseracing(interface& INT) {
    srand(time(0));
    int rd = rand() % 10;

    INT.output_in_game("\nWhich horse you think will run the fastest?\n", 4, true, true);
    INT.output_in_game("(Please enter a number between 1 - 10)\n", 4, false);

    int op = INT.input_in_game_int("A number between 1 - 10: ");
    while (op < 1 || op > 10)
        op = INT.input_in_game_int("Invalid input! please enter a number between 1 - 10: ");
    if (luck > 10) {
        INT.output_in_game("\nYour are extremely lucky (luck > 10)! You could always bet on the winning horse!\n", 2);
        INT.output_in_game("\nYou earned quite a bonus! [Money ++]\n\n", 2);
        money += 3000;
    } else {
        INT.output_in_game("\nThe winning horse number is [" + to_string(rd) + "] !\n");
        if (rd == op) {
            INT.output_in_game("\nYou earned quite a bonus! [Money ++]\n\n", 2);
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
}

// PART_TIME MODULE

bool player::do_part_time(interface& INT, bool reading) {
    int sz = parttimeId.size();
    if (sz == 0) {
        string text = "\n(You haven't received any job offer currently. Try visiting "
                      "some places or surfing the internet for some information.)\n\n";
        INT.output_in_game(text, 3, false, false, false, true);
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

void player::simulate_ordinary_week(interface& INT, bool reading, bool revision) {
    INT.clearwin_in_game();
    printValue(INT);

    string text = "It's the " + order[ord] + " week in " + month[mon] + ".\n\n";

// weather prompt?

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

    getch();
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

void player::simulate_first_semester(interface& INT) {

//    iq = eq = 3, courage = 4;
//    initLandscape(INT);
//    parttimeId.clear();
// for test
    expectedGrades = 0;
    pressure = 0;
    // September
    mon = 9;
    for (ord = 1; ord <= 4; ++ord)  simulate_ordinary_week(INT, false, false);

    // October
    mon = 10, ord = 1;
    simulate_ordinary_week(INT, false, false);
    ord = 2;
    simulate_ordinary_week(INT, true, false);
    for (ord = 3; ord <= 4; ++ord)  simulate_ordinary_week(INT, false, false);

    // November
    mon = 11;
    for (ord = 1; ord <= 4; ++ord)  simulate_ordinary_week(INT, false, false);

    mon = 12, ord = 1;
    simulate_ordinary_week(INT, false, true);
    ord = 2;
    
    getch();

    viewYourGrades[1] = expectedGrades;
}