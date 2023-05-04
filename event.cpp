#include "event.h"
#include <iostream>
#include <string>
#include <cstdlib>
#include <ctime>

using namespace std;

// This code defines functions of the Event class in C++.

// setProcess function sets the private member "process" of the current instance to the passed parameter "_process".
void Event::setProcess(int _process) {
    process = _process;
}

// getProcess function returns the private member "process" of the current instance.
int Event::getProcess() {
    return process;
}

// applyEvent function takes two parameters: a player object and an interface object. It doesn't modify the state of the Event object, instead always returns false.
bool Event::applyEvent(player& p, interface& INT) {
    return false;
};

// checktime function takes three integer parameters representing year, semester and week respectively. It returns true if these values are greater than or equal to the corresponding private members "year", "sem" and "week" of the current instance.
bool Event::checktime(int _year, int _sem, int _week) {
    return (_year >= year) && (_sem >= sem) && (_week >= week);
}

// This code defines the applyEvent function of the StrugglingInClass class in C++.

// The function takes two parameters: a player object and an interface object.
bool StrugglingInClass::applyEvent(player& p, interface& INT) {
    // If the current event's process is 3, return false. This means the event has already occurred.
    if (getProcess() == 3)
        return false;
    
    // If the above condition fails, there's a 50% chance of the event occurring.
    if ((rand() % 2) == 0) {
        // Display some text using the given Interface object.
        string text = "\nToday's lecture is extremely hard!\n";
        INT.output_in_game(text, 1, true, false, false, true);
        text = "\nYou decide to ...\n";
        INT.output_in_game(text, 4, true, true);
        text = "\n1. Struggling to keep up with the class!\n"
               "2. Just go blank and think nothing...\n";
        INT.output_in_game(text, 4, false);
        
        // Take user input to determine what to do next.
        int op = INT.input_in_game_int("Enter your choice: ");
        while (op != 1 && op != 2)  
            op = INT.input_in_game_int("Invalid input. Try again: ");
        
        // If the user chooses option 1, display some text and modify the player object's attributes accordingly.
        if (op == 1) {
            text = "\nYou've exhausted all your brain power... But it's worth it!\n"
                   "\n[Grades ++++]\n";
            INT.output_in_game(text, 2);
            text = "[Pressure +]\n"
                   "[IQ -]\n";
            INT.output_in_game(text, 3, true, false, false, true);
            p.setIq(p.getIq() - 1);
            p.setPressure(p.getPressure() + 1);
            p.setsGPA(p.getsGPA() + 0.4);
            
        // If the user chooses option 2, display some text and only modify the player object's pressure attribute accordingly.
        } else {
            text = "\nJust let it go with the wind....\n"
                   "\n[Pressure -]\n\n";
            INT.output_in_game(text, 2);
            p.setPressure(p.getPressure() - 1);
        } 
        
        // After modifying the player object attributes, print them to the console using the given Interface object.
        p.printValue(INT);
        // Set the current event's process to 3 (event has occurred).
        setProcess(3);
    }
    
    // Return false as this function doesn't actually end the game.
    return false;
}

// This code defines the applyEvent function of the MissingDeadline class in C++.

// The function takes two parameters: a player object and an interface object.
bool MissingDeadline::applyEvent(player& p, interface& INT) {
    // If the current event's process is 3, return false. This means the event has already occurred.
    if (getProcess() == 3)
        return false;
    
    // If the above condition fails and the player's IQ is less than 10, there's a 50% chance of the event occurring.
    if (p.getIq() < 10 && (rand() % 2) == 0) {
        // Display some text using the given Interface object.
        string text = "\nOops! You just found that you've missed an important deadline!!!\n";
        INT.output_in_game(text, 1, true, false, false, true);
        
        text = "\nImproving time management ability [IQ] may help you avoid such mistakes...\n"
                "\n[Pressure +]"
                "\n[Grades -]\n\n";
        INT.output_in_game(text, 3, true, false, false, true);
        
        // Modify the player object's pressure and sGPA attributes accordingly.
        p.setPressure(p.getPressure() + 1);
        p.setsGPA(p.getsGPA() - 0.08);
    } 
    
    // Print the player object's attributes to the console using the given Interface object.
    p.printValue(INT);
    // Set the current event's process to 3 (event has occurred).
    setProcess(3);
    // Return false as this function doesn't actually end the game.
    return false;
}
// This code defines the applyEvent function of the JoiningClubs class in C++.

// The function takes two parameters: a player object and an interface object.
bool JoiningClubs::applyEvent(player& p, interface& INT) {
    // If the current event's process is 3 or greater, return false as the event has already occurred.
    if (getProcess() >= 3)
        return false;
    
    // If the current event's process is 0, display some text using the given interface object to prompt user input.
    if (getProcess() == 0) {
        string text = "\nSome people say that joining a society is necessary part of university life.\n"
                      "Because it requires the [courage] to integrate into a new group.\n\n";
        INT.output_in_game(text, 4);
        text = "Are you interested in joining any student clubs / societies?\n\n";
        INT.output_in_game(text, 4, true, true);
        text = "\n1. Of course!\n"
               "2. I'm not a very social person...\n";
        INT.output_in_game(text, 4, false);
        int op = INT.input_in_game_int("Enter your choice: ");
        
        // Continue prompting user input until a valid option is selected.
        while (op != 1 && op != 2)
            op = INT.input_in_game_int("Invalid input. Try again: ");
        
        // If the user chooses option 1, check if their courage is sufficient for joining a club. Display appropriate text and update player attributes accordingly.
        if (op == 1) {
            text = "\n(Joining a student society requires certain amount of [courage])\n\n";
            INT.output_in_game(text, 3, true, false, false, true);
            if (p.getCourage() >= 10) {
                text = "You join a student society successfully!\n";
                       "[EQ ++++]\n\n";
                INT.output_in_game(text, 2);
                p.setEq(p.getEq() + 2);
                p.printValue(INT);
                setProcess(2);
                return false;
            } else {
                text = "It seems that your [courage] is not yet enough!\n"
                       "Try improve your [courage] to achieve this.\n\n";
                INT.output_in_game(text, 2);
                setProcess(1);
                return false;
            }
        } 
        
        // If the user chooses option 2, display appropriate text and update current event process accordingly.
        else {
            text = "\nWell, everyone has their own choice, not joining any clubs is also an experience.\n";
            INT.output_in_game(text, 2);
            setProcess(4);
            return false;
        }
    }
    
    // If the current event's process is 1, check again if the player's courage is now sufficient for joining a club. Display appropriate text and update player attributes accordingly.
    if (getProcess() == 1) {
        if (p.getCourage() >= 10) {
            string text = "\nBecause of your improved [courage], "
                    "You join a student society successfully!\n";
                    "[EQ ++++]\n\n";
            INT.output_in_game(text, 2);
            p.setEq(p.getEq() + 2);
            p.printValue(INT);
            setProcess(2);
            return false;
        }
    }
    
    // If the current event's process is 2 and the player's courage is now at least 20, display appropriate text and update player attributes accordingly.
    if (getProcess() == 2 && p.getCourage() >= 20) {
        string text = "\n[Enormous Courage] achieved! (courage >= 20)\n";
        INT.output_in_game(text, 1, true, false, false, true);
        text = "\nBecause of your outstanding performance in the club activities, "
               "you were unanimously elected as the president by the club members!\n\n"
               "[EQ ++++]\n"
               "[Courage ++]\n\n";
        INT.output_in_game(text, 2);
        p.setEq(p.getEq() + 4);
        p.setCourage(p.getCourage() + 2);
        p.printValue(INT);
        setProcess(3);
        return false;
    }
    
    // Return false as this function doesn't actually end the game.
    return false;
} 

// This function is called when the player wants to apply for an internship or a co-op.
bool InternshipOrCoop::applyEvent(player& p, interface& INT) {
    // If the application process has already started, return false.
    if (getProcess() >= 1)    
        return false;
    // Output a new email notification to the player.
    INT.output_in_game("\n\nNew email!\n", 2);
    // Output information about the internship/co-op to the player.
    INT.output_in_game("\nYou've received an email about a short-term internship in the following vacation.\n", 2);
    // Output options for the player to choose from.
    string text = "\nTry to apply?\n";
    INT.output_in_game(text, 4, true, true);
    text = "\n1. Of course! It will be an invaluable experience before I actually get to work.\n"
           "2. Nah, I have other plan right now.\n";
    INT.output_in_game(text, 4, false);
    // Get input from the player and validate it.
    int op = INT.input_in_game_int("Enter your choice: ");
    while (op != 1 && op != 2)  
        op = INT.input_in_game_int("Invalid input. Try again: ");
    // If the player chooses to apply, set the application process to started.
    if (op == 1) {
        INT.output_in_game("\nApplication sent! The result will be released in the end of semester.\n", 2);
        setProcess(1);      // need
    } else {
        // If the player chooses not to apply, set the application process to skipped.
        INT.output_in_game("\nMaybe next time. Seems you have other plans.\n", 2);
        setProcess(4);
    }
    return false;
}

// This function is called when the player wants to apply to study abroad.
bool StudyAbroad::applyEvent(player& p, interface& INT) {
    // If the application process has already started, return false.
    if (getProcess() >= 1)    
        return false;
    // Output a new email notification to the player.
    INT.output_in_game("\n\nNew email!\n", 2);
    // Output information about the study abroad opportunity to the player.
    INT.output_in_game("\nYou've received an email about a chance to study abroad in the following vacation!\n", 2);
    // Output options for the player to choose from.
    string text = "\nTry to apply? (This requires a lot of [money]!)\n";
    INT.output_in_game(text, 4, true, true);
    text = "\n1. Of course! It's always a good chance to exprience a different culture.\n"
           "2. Nah, I have other plan right now.\n";
    INT.output_in_game(text, 4, false);
    // Get input from the player and validate it.
    int op = INT.input_in_game_int("Enter your choice: ");
    while (op != 1 && op != 2)  
        op = INT.input_in_game_int("Invalid input. Try again: ");
    // If the player chooses to apply, set the application process to started.
    if (op == 1) {
        INT.output_in_game("\nApplication sent! The result will be released in the end of semester.\n", 2);
        setProcess(1);      // need
    } else {
        // If the player chooses not to apply, set the application process to skipped.
        INT.output_in_game("\nMaybe next time. Seems you have other plans.\n", 2);
        setProcess(4);
    }
    return false;
}
// This function allows a player to apply for a scholarship event.
bool Scholarships::applyEvent(player& p, interface& INT) {
    // If the process has already started, return false.
    if (getProcess() >= 1)    return false;
    
    // Notify the player of a new email.
    INT.output_in_game("\n\nNew email!\n", 2);
    INT.output_in_game("\nYou've received an email about a new student scholarship scheme.\n", 2);

    // Ask the player if they want to apply and provide options.
    string text = "\nTry to apply? (See your expected GPA in the right column)\n";
    INT.output_in_game(text, 4, true, true);
    text = "\n1. Of course! I think my GPA is enough to win the scholarship.\n"
           "2. Nah, I should improve my grades more before trying.\n";
    INT.output_in_game(text, 4, false);

    // Get the player's choice and validate it.
    int op = INT.input_in_game_int("Enter your choice: ");
    while (op != 1 && op != 2)  op = INT.input_in_game_int("Invalid input. Try again: ");

    // If the player chooses to apply, notify them that their application has been sent and set the process to 1.
    if (op == 1) {
        INT.output_in_game("\nApplication sent! The result will be released in the end of semester.\n", 2);
        setProcess(1);  // need
    } 
    // If the player chooses not to apply, notify them and set the process to 4.
    else {
        INT.output_in_game("\nHmmm, seems you are a very cautious person. \n", 2);
        setProcess(4);
    }
    // Return false.
    return false;
}
// This function allows a player to apply for a depression event.
bool Depression::applyEvent(player& p, interface& INT) {
    // If the player's pressure is greater than or equal to 10, display symptoms of depression and ask the player if they want to make an appointment with HKU health centre.
    if (p.getPressure() >= 10) {
        string text = "\nYou've been dizzy and weak lately and have insomnia...\n"
                      "You feel like you can't concentrate on things...\n\n";
        INT.output_in_game(text, 1, true, false, true);
        text = "You've built up too much pressure! ([pressure >= 10])\n"
               "These symptoms are precursors to [depression], a serious mental problem.\n\n";
        INT.output_in_game(text, 3, true, false, false, true);
        text = "Maybe you should make an appointment to HKU health centre?\n";
        INT.output_in_game(text, 4, true, true);
        text = "(Notice this will [take up the rest of your time], you cannot choose what to do afterwards)\n";
        INT.output_in_game(text, 4);
        text = "\n1. Yeah. I should take it seriously.\n"
               "2. I can't waste any time now. It's not a big deal.\n";
        INT.output_in_game(text, 4, false);

        // Get the player's choice and validate it.
        int op = INT.input_in_game_int("Enter your choice: ");
        while (op != 1 && op != 2)  op = INT.input_in_game_int("Invalid input. Try again: ");

        // If the player chooses to make an appointment, decrease their pressure and set the process to 1.
        if (op == 1) {
            text = "\nYou feel much more relaxed after talking to the therapist.\n"
                   "[Pressure ---]\n\n";
            INT.output_in_game(text, 2);
            p.setPressure(9);
            p.printValue(INT);
            setProcess(1);
            return true;
        } 
        // If the player chooses not to make an appointment, increase their pressure and set the process to 1.
        else {
            text = "\nYou feel that your headache is getting worse...\n"
                   "[Pressure +]\n\n";
            INT.output_in_game(text, 3, true, false, false, true);
            p.setPressure(p.getPressure() + 1);
            p.printValue(INT);
            setProcess(1);  // need
        }
    }
    // Return false.
    return false;
}

// This function applies an event to the player's relationship status.
bool Relationship::applyEvent(player& p, interface& INT) {
    // If the process is already completed, return false.
    if (getProcess() >= 3)  return false;
    
    // If the process is at stage 0, display a message and prompt the user for input.
    if (getProcess() == 0) {
        // Display a message with options for the user to choose from.
        string text = "\nAfter a long time together, you find that you gradually fall in love with a classmate..."
                      "Maybe now is a good time to confess your love...!!!\n"
                      "This requires quite a [courage] and [charisma / EQ]\n\n";
        INT.output_in_game(text, 4);
        // Display another message with more options for the user to choose from.
        text = "Take a try! Maybe he/she is your Mr./Mrs. Right!\n\n";
        INT.output_in_game(text, 4, true, true);
        text = "\n1. Of course! I got the feeling that Cubit favours me today...\n"
               "2. ...I'm still not sure about that...\n";
        INT.output_in_game(text, 4, false);
        // Prompt the user for input and validate it.
        int op = INT.input_in_game_int("Enter your choice: ");
        while (op != 1 && op != 2)
            op = INT.input_in_game_int("Invalid input. Try again: ");
        
        // If the user chooses option 1, display a message and update player stats accordingly.
        if (op == 1) {
            text = "\n(Ask someone out and establish a romantic relationship requires certain amount of [courage] and [charisma / EQ]...)\n\n";
            INT.output_in_game(text, 3, true, false, false, true);
            if (p.getCourage() >= 15 && p.getEq() >= 20) {
                text = "It seems that he/she is also interested in you! You are not single anymore!\n"
                       "[EQ ++++]\n\n";
                INT.output_in_game(text, 2);
                p.setEq(p.getEq() + 2);
                p.printValue(INT);
                setProcess(2);
                return false;
            } else {
                text = "He/She thinks you are joking! Seems you are still in the friendzone for now...\n"
                       "It seems that your [courage] and [charisma / EQ] is not yet enough!\n"
                       "Try improve your [courage] and [charisma / EQ] to achieve this.\n\n";
                INT.output_in_game(text, 2);
                setProcess(1);
                return false;
            }
        // If the user chooses option 2, update process status and return false.
        } else {
            setProcess(4);
            return false;
        }
    }
    // If the process is at stage 1, check if player stats are high enough to progress.
    if (getProcess() == 1) {
        if (p.getCourage() >= 15 && p.getEq() >= 20) {
            string text = "Today you ask your crush out since you are attractive enough...!\n"
                          "It seems that he/she is also interested in you! You are not single anymore!\n"
                          "[EQ ++]\n"
                          "[Pressure ----]\n\n";
            INT.output_in_game(text, 2);
            p.setEq(p.getEq() + 2);
            int tmp = p.getPressure() - 4;
            if (tmp < 0)    tmp = 0;
            p.setPressure(tmp);
            p.printValue(INT);
            setProcess(2);
            return false;
        }
    }
    // If the process is at stage 2, check if player EQ is high enough to progress.
    if (getProcess() == 2 && p.getEq() >= 30) {
        string text = "\n[Enormous Charisma] achieved! (EQ >= 30)\n";
        INT.output_in_game(text, 1, true, false, false, true);
        text = "\nAlthough it may be corny to say so, after so much time together, "
               "you are sure that your lover will be with you for the whole life...\n\n"
               "[EQ ++++]\n"
               "[Courage ++]\n"
               "[Pressure ----]\n\n";
        INT.output_in_game(text, 2);
        p.setEq(p.getEq() + 4);
        p.setCourage(p.getCourage() + 2);
        int tmp = p.getPressure() - 4;
        if (tmp < 0)    tmp = 0;
        p.setPressure(tmp);
        p.printValue(INT);
        setProcess(3);
        return false;
    }
    
    return false;
}
// This function is a member function of the Minor class, which applies an event related to choosing a minor for the player.
bool Minor::applyEvent(player& p, interface& INT) {
    // If the process has already been completed or has reached a certain stage, return false.
    if (getProcess() >= 3)  return false;
    // If the process hasn't started yet, output the initial message and options for the player to choose.
    if (getProcess() == 0) {
        // Output the message about the importance of choosing a minor and the requirement of intelligence.
        string text = "\nToday's society needs complex talents, therefore, you have the idea of choosing a minor.\n"
                        "This requires quite a [intelligence / IQ]\n\n";
        INT.output_in_game(text, 4);
        // Output the message about the pros and cons of choosing a minor.
        text = "Choosing a minor may improve your competence, but your academic [stress] will increase significantly...\n";
        INT.output_in_game(text, 4, true, true);
        // Output the options for the player to choose.
        text = "\n1. Of course! I need to widen my horizon...\n"
                "2. Specializing in my current field may be a better choice...\n";
        INT.output_in_game(text, 4, false);
        // Get the input from the player and validate it.
        int op = INT.input_in_game_int("Enter your choice: ");
        while (op != 1 && op != 2)
            op = INT.input_in_game_int("Invalid input. Try again: ");
        // If the player chooses option 1, check if their intelligence is high enough and output the corresponding message and update the player's attributes.
        if (op == 1) {
            text = "\n(Choosing a minor requires certain amount of [intelligence / IQ]...)\n\n";
            INT.output_in_game(text, 3, true, false, false, true);
            if (p.getIq() >= 20) {
                text = "You've chosen a minor of your interest. Work harder!\n"
                       "[IQ ++++]\n"
                       "[Grades ++]\n\n";
                INT.output_in_game(text, 2);
                p.setIq(p.getIq() + 4);
                p.setsGPA(p.getsGPA() + 0.3);
                text = "[Pressure ++++]\n\n";
                INT.output_in_game(text, 3, true, false, false, true);
                p.setPressure(p.getPressure() + 4);
                p.printValue(INT);
                setProcess(3);
                return false;
            } else { // If the player's intelligence is not high enough, output the corresponding message and update the process stage.
                text = "Your current learning ability is not sufficient to support your choice of a minor...\n"
                        "It seems that your [courage] and [charisma / EQ] is not yet enough!\n"
                        "Try improve your [courage] and [charisma / EQ] to achieve this.\n\n";
                INT.output_in_game(text, 2);
                setProcess(1);
                return false;
            }
        } else { // If the player chooses option 2, update the process stage and return false.
            setProcess(4);
            return false;
        }
    }
    // If the process has started but hasn't finished yet, check if the player's intelligence is high enough and output the corresponding message and update the player's attributes.
    if (getProcess() == 1) {
        if (p.getIq() >= 20) {
            string text = "Today you review your ability and find that ---\n"
                          "You are now able to choose a minor: your improved learning ability gives you confidence!\n"
                          "You've chosen a minor of your interest. Work harder!\n"
                          "[IQ ++++]\n"
                          "[Grades ++]\n\n";
            INT.output_in_game(text, 2);
            p.setIq(p.getIq() + 4);
            p.setsGPA(p.getsGPA() + 0.3);
            text = "[Pressure ++++]\n\n";
            INT.output_in_game(text, 3, true, false, false, true);
            p.setPressure(p.getPressure() + 4);
            p.printValue(INT);
            setProcess(3);
            return false;
        }
    }
    // If none of the conditions above is met, return false.
    return false;
}

// This function is a member function of the GraduateCapstone class. It takes in two parameters: 
// a player object and an interface object. It returns a boolean value.
bool GraduateCapstone::applyEvent(player& p, interface& INT) {
    // If the process is already completed, return false.
    if (getProcess() >= 3)  return false;
    // If the process hasn't started yet, run this block of code.
    if (getProcess() == 0) {
        // Create a string variable with a message to be displayed in the game.
        string text = "\nYou are about to graduate! Before that, you [must] complete your capstone project!\n"
                        "This requires your [comprehensive] ability!\n\n";
        // Output the message to the interface object with a specific format.
        INT.output_in_game(text, 4);
        // Check if the player's IQ, EQ, courage, and luck values meet the requirements to complete the capstone project.
        if (p.getIq() >= 30 && p.getEq() >= 20 && p.getCourage() >= 20 && p.getLuck() >= 10) {
            // If the requirements are met, display this message and decrease the player's pressure value by 3.
            text = "You've prepared very well for your final year capstone project!\n"
                   "No need to worry about graduation now...\n"
                   "[Pressure ---]\n\n";
                INT.output_in_game(text, 2);
                int tmp = p.getPressure() - 3;
                if (tmp < 0)    tmp = 0;
                p.setPressure(tmp);
                p.printValue(INT);
                // Change the process value to 3 and return false.
                setProcess(3);
                return false;
        } else {
            // If the requirements are not met, display a message indicating which requirement was not met.
            text = "It seems that your current ability is not sufficient to complete your final year capstone project...\n";        
            INT.output_in_game(text, 2);
            if (p.getIq() < 30) {
                text = "\n(Intelligence / IQ not enough!)\n";
                INT.output_in_game(text, 3, true, false, false, true);
            }
            if (p.getEq() < 20) {
                text = "\n(Charisma / EQ not enough!)\n";
                INT.output_in_game(text, 3, true, false, false, true);
            }
            if (p.getCourage() < 20) {
                text = "\n(Courage not enough!)\n";
                INT.output_in_game(text, 3, true, false, false, true);
            }
            if (p.getIq() < 10) {
                text = "\n(Luck not enough!)\n";
                INT.output_in_game(text, 3, true, false, false, true);
            }
            // Change the process value to 1 and return false.
            setProcess(1);
            return false;
        }
    }
    // If the process has started but not completed, run this block of code.
    if (getProcess() == 1) {
        // Check if the player's IQ, EQ, courage, and luck values meet the requirements to complete the capstone project.
        if (p.getIq() >= 30 && p.getEq() >= 20 && p.getCourage() >= 20 && p.getLuck() >= 10) {
            // If the requirements are met, display this message and decrease the player's pressure value by 3.
            string text = "Today you review your ability and find that ---\n"
                          "You've prepared very well for your final year capstone project!\n"
                          "No need to worry about graduation now...\n"
                          "[Pressure ---]\n\n";
            INT.output_in_game(text, 2);
            int tmp = p.getPressure() - 3;
            if (tmp < 0)    tmp = 0;
            p.setPressure(tmp);
            p.printValue(INT);
            // Change the process value to 3 and return false.
            setProcess(3);
            return false;
        }
    }    
    // If none of the above conditions are met, return false.
    return false;
}
// This function applies an event for the player.
// It checks if the process is less than 3 and a random number is divisible by 3.
bool WatchDanceShow::applyEvent(player& p, interface& INT) {
    if (getProcess() >= 3)  return false; // If the process is greater than or equal to 3, return false.
    if (random() % 3 != 0)  return false; // If a random number is not divisible by 3, return false.
    
    // Set text to display in the game.
    string text = "\nOn the way home, you see that the HKU dancing society (DANSO) "
                  "is holding a dancing competition!\n\n";
    // Output the text to the game with formatting options.
    INT.output_in_game(text, 1, true);
       
    text = "Seems brilliant! Want to check it out?\n";
    INT.output_in_game(text, 4, true, true);
    text = "(Notice this will [take up the rest of your time], you cannot choose what to do afterwards)\n";
    INT.output_in_game(text, 4);
    text = "\n1. Yeah. I always love dancing!\n"
           "2. Nah, I have other plan afterwards.\n\n";
    INT.output_in_game(text, 4, false);
    
    // Get user input and validate it.
    int op = INT.input_in_game_int("Enter your choice: ");
    while (op != 1 && op != 2)  op = INT.input_in_game_int("Invalid input. Try again: ");
    
    // If the user chooses option 1, update the player's stats and return true.
    if (op == 1) {
        text = "\nThe dancers' wonderful dance moves teach you what glamour is all about...\n"
               "[Charisma / EQ ++]\n"
               "[Pressure --]\n\n";
        INT.output_in_game(text, 2);
        int tmp = p.getPressure() - 2;
        if (tmp < 0)    tmp = 0;
        p.setPressure(tmp);
        p.setEq(p.getEq() + 2);
        p.printValue(INT);
        setProcess(3);
        return true;
    } 
    // If the user chooses option 2, return false.
    return false;
}
// This function applies an event for the player.
// It checks if the process is less than 3 and a random number is divisible by 3.
bool WatchDebateCompetition::applyEvent(player& p, interface& INT) {
    if (getProcess() >= 3)  return false; // If the process is greater than or equal to 3, return false.
    if (random() % 3 != 0)  return false; // If a random number is not divisible by 3, return false.
    
    // Set text to display in the game.
    string text = "\nOn the way home, you see that the HKU Debating Society "
                  "is holding a debating competition!\n\n";
    // Output the text to the game with formatting options.
    INT.output_in_game(text, 1, true);
       
    text = "Seems interesting! Want to check it out?\n";
    INT.output_in_game(text, 4, true, true);
    text = "(Notice this will [take up the rest of your time], you cannot choose what to do afterwards)\n";
    INT.output_in_game(text, 4);
    text = "\n1. Yeah. I always love debating!\n"
           "2. Nah, I have other plan afterwards.\n\n";
    INT.output_in_game(text, 4, false);
    
    // Get user input and validate it.
    int op = INT.input_in_game_int("Enter your choice: ");
    while (op != 1 && op != 2)  op = INT.input_in_game_int("Invalid input. Try again: ");
    
    // If the user chooses option 1, update the player's stats and return true.
    if (op == 1) {
        text = "\nThe brilliant expressions of the debaters make you think more critically...\n"
               "[Intelligence / IQ ++]\n"
               "[Charisma / EQ ++]\n"
               "[Pressure -]\n\n";
        INT.output_in_game(text, 2);
        int tmp = p.getPressure() - 1;
        if (tmp < 0)    tmp = 0;
        p.setPressure(tmp);
        p.setEq(p.getEq() + 2);
        p.setIq(p.getIq() + 2);
        p.printValue(INT);
        setProcess(3);
        return true;
    } 
    // If the user chooses option 2, return false.
    return false;
}
// This function applies an event for the player.
// It checks if the process is less than 3 and a random number is divisible by 3.
bool GotoChurch::applyEvent(player& p, interface& INT) {
    if (getProcess() >= 3)  return false; // If the process is greater than or equal to 3, return false.
    if (random() % 3 != 0)  return false; // If a random number is not divisible by 3, return false.
    
    // Set text to display in the game.
    string text = "\nOn the university street, A strange person suddenly approaching you and "
                  "asks if you would like to sit in on a sermon.\n\n";
    // Output the text to the game with formatting options.
    INT.output_in_game(text, 1, true);
       
    text = "You don't look like a religious person...want to take a look?\n";
    INT.output_in_game(text, 4, true, true);
    text = "(Notice this will [take up the rest of your time], you cannot choose what to do afterwards)\n";
    INT.output_in_game(text, 4);
    text = "\n1. Yeah. May get some enlightment there!\n"
           "2. Nah, I have other plan afterwards.\n\n";
    INT.output_in_game(text, 4, false);
    
    // Get user input and validate it.
    int op = INT.input_in_game_int("Enter your choice: ");
    while (op != 1 && op != 2)  op = INT.input_in_game_int("Invalid input. Try again: ");
    
    // If the user chooses option 1, update the player's stats and return true.
    if (op == 1) {
        text = "\nThe priest's devotional sermon seems to have made your heart purer...\n"
               "[Luck ++]\n"
               "[Courage ++]\n"
               "[Pressure -]\n\n";
        INT.output_in_game(text, 2);
        int tmp = p.getPressure() - 1;
        if (tmp < 0)    tmp = 0;
        p.setPressure(tmp);
        p.setLuck(p.getLuck() + 2);
        p.setCourage(p.getCourage() + 2);
        p.printValue(INT);
        setProcess(3);
        return true;
    } 
    // If the user chooses option 2, return false.
    return false;
}
