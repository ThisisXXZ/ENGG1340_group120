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

void player::colorPrint(string s, int col) {
    cout << s << endl;
}

void player::initName() {
    string text = "What is your name? (English only)\n";
    colorPrint(text, 5);
    cin.ignore();
    getline(cin, name);
}

void player::initSex() {
    string text = "\nWhat is your gender?\n";
    colorPrint(text, 5);
    text = "(0 for male, 1 for female. 2 if you don't care and want to set it randomly)\n";
    colorPrint(text, 4);
    cin >> sex;
    while (sex < 0 || sex > 2) {
        cout << "I don't believe you will make mistakes in such things. It's a joke, right?\n";
        cout << "Try again: ";
        cin >> sex;
    }
    if (sex == 2)
        sex = rand() % 2;
    text = "\nOf course you are a " + (string)(sex ? "[girl]" : "[boy]") + ". I mean, who will doubt that?\n\n";
    colorPrint(text, 15);
}

void player::initVal() {
    string text = "Could you give a brief introduction on your academic achievements, "
                  "your personality and how willing you are to try new things?\n\n";
    colorPrint(text, 5);
    text = "(Here you are going to input 3 integers a, b and c, and their sum "
           "a + b + c = 10. [a] represents your [academic intelligence], [b] represents "
           "your [charisma] and [c] represents your [courage].)\n\n"
           "(Be careful! Your allocation will influence your university life.)\n\n";
    colorPrint(text, 4);
    while (true) {
        string op;
        cout << "Your prompt here: \n";
        cin >> iq >> eq >> courage;
        if (iq < 0 || eq < 0 || courage < 0) {
            cout << "Negative number? It's a joke of some kind, right?\n\n";
            continue;
        }
        if (iq + eq + courage > 10) {
            cout << "The sum of 3 numbers exceeds 10. Take your time, don't be too nervous.\n\n";
        } else if (iq + eq + courage < 10) {
            cout << "The sum of 3 numbers is below 10. Don't be so humble!\n\n";
        } else {
            break;
        }
    }
    cout << endl;
}

void player::initSkill() {
    string text = "What else talents you want to specify?\n\n";
    colorPrint(text, 5);
    text = "(You may choose at most 4 [talents] of yours. However, no one is perfect. " 
           "Every 2 [talents] may result in 1 random [shortcoming]. However, "
           "[shortcomings] could be overcome in the future.)\n\n";
    colorPrint(text, 4);

    text = "(You grab your pen tightly, thinking...)\n\n";
    colorPrint(text, 1);

    // This part should be randomized and objectivize
    text = "1. You come from a very rich family.\n   "
           "(Skill [Money talks]: Don't worry, you got money. A lot!)\n"
           "2. You are born with good luck.\n   "
           "(Skill [Luck is also strength]: You are more likely to success in some random events.)\n\n";
    string ski;
    cout << text;
    cin.ignore();
    getline(cin, ski);
    
    cout << "!!!(This part needs further developing: Skills & Shortcomings needed!!!)\n\n";
}

void player::printTranscript() {

//    HANDLE handle = GetStdHandle(STD_OUTPUT_HANDLE);
//    SetConsoleTextAttribute(handle, FOREGROUND_INTENSITY | 5);
    cout << "+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++\n";
//    Sleep(200);
    cout << "+     [the University of Hong Kong: Application form]     +\n";
//   Sleep(200);
    cout << "+                                                         +\n";
//    Sleep(200);
    cout << "+                                                         +\n";
//    Sleep(200);
    cout << "+ Name: " << left << setw(50) << name << "+\n";
//    Sleep(200);
    cout << "+                                                         +\n";
//    Sleep(200);
    cout << "+ Sex: " << left << setw(51) << (string)(sex ? "female" : "male") << "+\n";
//    Sleep(200);
    cout << "+                                                         +\n";
//    Sleep(200);
    cout << "+ Academic talents: " << left << setw(38) << iq << "+\n";
//    Sleep(200);
    cout << "+ Charisma: " << left << setw(46) << eq << "+\n";
//    Sleep(200);
    cout << "+ Courage: " << left << setw(47) << courage << "+\n";
//    Sleep(200);
    cout << "+                                                         +\n";
//    Sleep(200);
    cout << "+ Skills (needs developing...)                            +\n";
//    Sleep(200);
    cout << "+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++\n\n";
//    SetConsoleTextAttribute(handle, FOREGROUND_INTENSITY | 7);
}

void player::init(interface& INT) {
    srand(time(0));
    std::string text = "After all these years of hard work, You've "
                       "finally got the chance to be admitted into HKU!\n"
                       "This is the school of your dream; you know you have to take the chance.\n"
                       "Now you are about to face your final challenge: completing the application"
                       " form.\n\n";
    INT.output_in_game(text);
    text = "(Your fingers are trembling with nervousness.)\n";
    INT.output_in_game(text, 1, true, true, true, true);
    sleep(2);
    text = "\n\n[the University of Hong Kong: Application form]\n\n";
    INT.output_in_game(text);
    getch();

/*
    initName();
    initSex();
    initVal();
    initSkill();

    text = "Finished, finally!\n"
           "(You drop your pen, checking the application form carefully.)\n\n";
    colorPrint(text, 1);

    while (true) {
        printTranscript();

        text = "It seems perfect, except...\n\n";
        colorPrint(text, 5);
        text = "1. Nuh, that's it. You are ready to submit it. \n"
               "2. There's a typo in the name and you want to change it. \n"
               "3. You realize you've written the wrong gender. Come on, seriously? \n"
               "4. You want to reallocate your talents, charisma and courage. \n"
               "5. You want to modify your skills. \n\n";
        colorPrint(text, 7);
        cout << "Your prompt here: ";
        int op;
        cin >> op;
        while (op < 1 || op > 5) {
            cout << "Invalid input.\n Your prompt here: ";
            cin >> op;
        }
        if (op == 1) {
            text = "\n(Submitted succesfully. You let out a deep sigh and wait for the results with hope.)\n\n";
            colorPrint(text, 1);
            break;
        } else if (op == 2) {
            cout << '\n';
            initName();
        } else if (op == 3) {
            cout << '\n';
            initSex();
        } else if (op == 4) {
            cout << '\n';
            initVal();
        } else if (op == 5) {
            cout << '\n';
            initSkill();
        }

    }
    */
}

