# ENGG1340/COMP2113 group120: HKU Student Simulator

## Team Members
Listed in **alphabetical order**, in the format of *real name (Github ID)*

1. Chen Yanning (**illufluo** chenyanning)
2. Lu Jiayang (**Linus-Lu** Linus)
3. Wang Yao (**DorisssW**)
4. Xiong Xinzhuang (**ThisisXXZ** XXZ)
5. Xu Haoyi (**xuZinogre**)

## Game Description

This is a game that enables players to experience four-year university life as a HKU student. 

**On weekly basis**, you can do whatever you want: just staying at library,  surfing the Internet, doing part-time jobs or even exploring the Hong Kong city, and each choice of yours may decide your unpredictable future. There are various random events and several major challenges in the game for you to explore and accomplish.

Try and enjoy it!

**The game is for entertainment only and has nothing to do with reality.** (**P.S. As a group of first-year students, we have limited imagination about the entire four-year university life...**)

## Game Instruction

The instructions below will be very **useful**, so please read them carefully.

### Before the Game Starts (compilation and execution)
* For the best experience, please change your **terminal size** to $30 \times 120$ with the command ``resize -s 30 120``
* Generate the executable game file with the command ``make main``
* Start the game with ``./main``

### In-game Interaction Instructions
You (the player) only interact with game (input) in the following **two** cases:
* The game prompt you for input: in this case, you may find the cursor **blinking** at the specified input position.
* The game freezes (always because a new scene will appear) and wait for you to react: in this case, you may find the cursor fixing in the **upper left corner.**

The above two cases have one thing in common, which is that the text has been fully displayed on the screen.

Always remember that **do NOT enter anything when the text is displaying on the screen** !

### Save & Load Instructions

This game simulates a HKU student's life on a weekly basis. 

You could save the game at any **week** you want and load the game afterwards to continue playing.

* Save the current game

    **At the end of each week**, the game will wait for you to **press any key** to begin next week's simulation.
    
    If you press **"s"** (stands for "save"), you will enter the saving page.    
    Follow the in-game instructions and you could save the current game.

* Load the previous game

   You could load any previous saved game in the **main page**.
   
* Handling saving files

   You could delete all the saving files with the command ``make cleanSave``
  
## Implemented Features

### Random event

During the game, you have the opportunity to encounter various random events. 
They are classes derived from the base class ``Event``, and a vector ``randomEvent`` stores all the derived class pointers.

**Requirement satisfaction**: Generation of random game sets or events, data structures for storing game status, dynamic memory management

### Landmark module

During the game, you could explore different landmarks in Hong Kong. All the places and corresponding events are stored in a map ``initItems``, and each element in this map is a vector. (``initItems[place]`` stores all the events in the place ``place``. ) And all the places that player already explored will be stored in the vector ``unlockedLandscape``.

**Requirement satisfaction**: data structures for storing game status, dynamic memory management

### Multiple files

The program code is divided into multiple files. Every header files (included **classes declarations**) and corresponding cpp files (included **classes implementation**) are reponsible for a seperate module.

**Requirement satisfaction**: program codes in multiple files

### Save & Load functions

The game provides save & load functions. The game status include player's information, current game time and progress of events. We use the txt file ``Save#[id].txt`` to represent a game status. In this process, file pointers, ``ifstream`` object and ``ofstream`` object are used.

**Requirement satisfaction**: file input/output, data structures for storing game status

## Non-standard Libraries Usage

### ncurses.h

The library ``ncurses.h`` provides support to implement the game interfaces and manipulate multiple windows. 

The interface module (including ``interface.h`` and ``interface.cpp``) is mostly based on ncurses library. Also, the in-game texts style (color, underlined, bold) is also controlled using the ``attron()`` function in the ncurses library.

### unistd.h

The in-game texts appears in **typewriter style**: every character will appear in the screen with tiny-time pause. The ``sleep()`` function in the library ``unistd.h`` help create the time pause.

<br />

ReadMe Editors: Xiong Xinzhuang, Xu Haoyi, Wang Yao 
