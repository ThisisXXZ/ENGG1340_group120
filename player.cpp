#include <iostream>
#include <iomanip>
#include <string>
#include <cstdlib>
#include <ctime>
#include <cstdio>
#include <unistd.h>
#include <fstream>
#include <sstream>
#include "player.h"
#include "interface.h"

using namespace std;

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
           "your [charisma] and [c] represents your [courage].)\n\n"
           "(Be careful! Your allocation will influence your university life.)\n\n";
    INT.output_in_game(text, 4);
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

void player::printValue(WINDOW* rht, WINDOW* fa, string mon, int ord) {

    wmove(rht, 1, 2);
    wclrtoeol(rht);
    wprintw(rht, "%s: week %d", mon.c_str(), ord);
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
    wprintw(rht, "Grades: %g", expectedGrades);
    wmove(rht, 10, 2);
    wclrtoeol(rht);
    wprintw(rht, "Pressure: %d", pressure);
    box(rht, '+', '.');
    touchwin(fa);
    wrefresh(fa);
}

void player::printTranscript(interface& INT) {

    INT.output_in_game("+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++\n", 2, false);
    sleep(1);
    INT.output_in_game("+     [the University of Hong Kong: Application form]     +\n", 2, false);
    sleep(1);
    INT.output_in_game("+                                                         +\n", 2, false);
    sleep(1);
    INT.output_in_game("+                                                         +\n", 2, false);
    sleep(1);
    INT.output_in_game(name, 2, false, false, false, false, "+ Name: %-50s+\n");
    sleep(1);
    INT.output_in_game("+                                                         +\n", 2, false);
    sleep(1);
    INT.output_in_game((string)(sex ? "female" : "male"), 2, false, false, false, false, "+ Sex: %-51s+\n");
    sleep(1);
    INT.output_in_game("+                                                         +\n", 2, false);
    sleep(1);
    INT.output_in_game(to_string(iq), 2, false, false, false, false, "+ Academic talents: %-38s+\n");
    sleep(1);
    INT.output_in_game(to_string(eq), 2, false, false, false, false, "+ Charisma: %-46s+\n");
    sleep(1);
    INT.output_in_game(to_string(courage), 2, false, false, false, false, "+ Courage: %-47s+\n");
    sleep(1);
    INT.output_in_game("+                                                         +\n", 2, false);
    sleep(1);
    INT.output_in_game("+ Skills (needs developing...)                            +\n", 2, false);
    sleep(1);
    INT.output_in_game("+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++\n\n", 2, false);
}

void player::init(interface& INT) {
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
        INT.output_in_game(text, 4);
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

string month[] = {"", "January", "February", "March", 
                    "April", "May", "June", "July", 
                    "August", "September", "October", 
                    "November", "December"};

string order[] = {"", "first", "second", "third", "fourth"};

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

string player::doelse_prompt() {
    if (pressure >= 10)
        return "(You are under too much stress! Maybe you should do something else to change your mood.)\n";
    return "(University is NOT all about study. Let's see what else you can do!)\n";
}

string act[3] = {"watched a popular TV series!\n", 
                 "played a video game for a while!\n", 
                 "watched a famous movie!\n"};

void player::surf_the_internet(interface& INT) {        // news module could be created
    srand(time(0));
    INT.output_in_game("You " + act[rand() % 3], 2);
    INT.output_in_game("[pressure --]", 2);
    pressure -= 2;
    if (pressure < 0)   pressure = 0;
}

void player::simulate_ordinary_week(interface& INT, int mon, int ord) {
    INT.clearwin_in_game();
    printValue(INT.get_rhtwin(), INT.get_gamewin(), month[mon], ord);

    string text = "It's the " + order[ord] + " week in " + month[mon] + ".\n"
                  "[weather prompt (developing...)]\n[advice prompt (developing...)]\n\n";

    INT.output_in_game(text);

    text = "It's an ordinary teaching week --- attending the courses improves your expected grades!\n"
           "[grades +]\n";
    expectedGrades += 0.1;
    printValue(INT.get_rhtwin(), INT.get_gamewin(), month[mon], ord);
    INT.output_in_game(text, 2);


    INT.output_in_game("\n So, What's your plan?\n\n", 4, true, true);
    text = "1. Spend all your spare time in main library / Chi Wah learning common.\n"
           "  " + study_prompt(); 
    INT.output_in_game(text, 4, false);
    text = "\n2. Do something else.\n"
           "  " + doelse_prompt();
    INT.output_in_game(text, 4, false);

    int op = INT.input_in_game_int();
    while (op != 1 && op != 2)  op = INT.input_in_game_int("Invalid input: try again: ");
    if (op == 1) {
        text = "\nSpent a fufilling time at the main library...\n"
               "[grades +++]\n"
               "[pressure +]\n";
        expectedGrades += 0.2 * (1.0 + iq / 10.0) * (1.0 - pressure / 10.0);
        pressure += 1;
        printValue(INT.get_rhtwin(), INT.get_gamewin(), month[mon], ord);
        INT.output_in_game(text, 2);
    }
    if (op == 2) {
        int op_2 = 0;
        do {
            INT.output_in_game("\n It's time for relaxing! What do you want to do?\n\n", 1, true, true);
            text =  "1. Go somewhere else.\n"
                    "   (Explore new place! Meet new people!)\n\n"
                    "2. Spend the time on the Internet.\n"
                    "   (Someone call it a waste of time, that's because they use it in a wrong way.)\n\n"
                    "3. Do part-time jobs.\n"
                    "   (Money and experience. Kill two birds with one stone)\n\n";
            INT.output_in_game(text, 1, false);
            op_2 = INT.input_in_game_int();
            while (op_2 != 1 && op_2 != 2 && op_2 != 3) 
                op_2 = INT.input_in_game_int("Invalid input. Try again: ");
            if (op_2 == 1) {
/*
In this section, player could explore many different landmarks
go to each landmark has different effects
some landmark could facilitate as store, selling special items

landmark module needed
*/                
                break;
            }
            if (op_2 == 2) {
                surf_the_internet(INT);
                break;
            }
            if (op_2 == 3) {
/*
player could choose different places to do part-time.
3 part-time jobs could be designed.
1: +1000
2: +600 courage + 1
3: +800 eq + 1
*/
                break;
            }
        } while (true);
        
        
    }

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
    expectedGrades = 0;
    pressure = 0;
    simulate_ordinary_week(INT, 9, 1);
    viewYourGrades[1] = expectedGrades;
}

// Save the player's game to the specified file
bool Player::save_game(const string &filename) {
    ofstream save_file(filename);
    // If the file fails to open, return false
    if (!save_file.is_open()) {
        return false;
    }
    // Save player attributes to the file
    save_file << name << endl;
    save_file << iq << endl;
    save_file << eq << endl;
    save_file << courage << endl;
    save_file << luck << endl;
    save_file << sex << endl;
    save_file << gpa << endl;
    // Close the file
    save_file.close();
    return true;
}

// Load the player's game from the specified file
bool Player::load_game(const string &filename) {
    ifstream load_file(filename);
    // If the file fails to open, return false
    if (!load_file.is_open()) {
        return false;
    }
    string line;
    // Read player attributes from the file and assign them to the Player object
    if (getline(load_file, line)) {
        name = line;
    } else {
        return false;
    }
    if (getline(load_file, line)) {
        iq = stoi(line);
    } else {
        return false;
    }
    if (getline(load_file, line)) {
        eq = stoi(line);
    } else {
        return false;
    }
    if (getline(load_file, line)) {
        courage = stoi(line);
    } else {
        return false;
    }
    if (getline(load_file, line)) {
        luck = stoi(line);
    } else {
        return false;
    }
    if (getline(load_file, line)) {
        sex = stoi(line);
    } else {
        return false;
    }
    if (getline(load_file, line)) {
        gpa = stod(line); //convert a string to a double
    } else {
        return false;
    }
    load_file.close();
    return true;
}
