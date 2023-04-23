#include <iostream>
#include <iomanip>
#include <string>
#include <cstdlib>
#include <ctime>
#include <cstdio>
#include <unistd.h>
#include "player.h"
#include "interface.h"

using namespace std;

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
    int in = INT.input_in_game_int();
    while (in != 0 && in != 1 && in != 2) {
        text = "\nI don't believe you will make mistakes in such things. It's a joke, right?\n";
        INT.output_in_game(text, 2);
        in = INT.input_in_game_int("Try again: ");
    }
    if (in == 2)  sex = rand() % 2;
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

void player::printTranscript(interface& INT) {

    INT.output_in_game("+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++\n", 2, false);
    sleep(0.5);
    INT.output_in_game("+     [the University of Hong Kong: Application form]     +\n", 2, false);
    sleep(0.5);
    INT.output_in_game("+                                                         +\n", 2, false);
    sleep(0.5);
    INT.output_in_game("+                                                         +\n", 2, false);
    sleep(0.5);
    INT.output_in_game(name, 2, false, false, false, false, "+ Name: %-50s+\n");
    sleep(0.5);
    INT.output_in_game("+                                                         +\n", 2, false);
    sleep(0.5);
    INT.output_in_game((string)(sex ? "female" : "male"), 2, false, false, false, false, "+ Sex: %-51s+\n");
    sleep(0.5);
    INT.output_in_game("+                                                         +\n", 2, false);
    sleep(0.5);
    INT.output_in_game(to_string(iq), 2, false, false, false, false, "+ Academic talents: %-38s+\n");
    sleep(0.5);
    INT.output_in_game(to_string(eq), 2, false, false, false, false, "+ Charisma: %-46s+\n");
    sleep(0.5);
    INT.output_in_game(to_string(courage), 2, false, false, false, false, "+ Courage: %-47s+\n");
    sleep(0.5);
    INT.output_in_game("+                                                         +\n", 2, false);
    sleep(0.5);
    INT.output_in_game("+ Skills (needs developing...)                            +\n", 2, false);
    sleep(0.5);
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
    
   getch();
}

