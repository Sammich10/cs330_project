# CS330 Coding Assignment

## Usage
Do use this program, ensure you have C/C++ and G++ compiler installed on your system.
This program was created and tested on Ubuntu 22.04.1 LTS using Vim and VSCode. 

To run the program, clone the repository, and navigate to the directory you cloned it in using the 
Ubuntu terminal emulator. Type and run "make" to compile the program.

## How-to (lockengine.o)
After compiling the source code with 'make', run './lockengine.o' in the terminal.

You may then start to type in digits. When the correct unlock sequence is typed in, the program will print "Unlocked!",
and likewise when the lock sequence is typed in, it will print "Locked!". 

To exit the program, either type the character 'q' or use the 'ctrl+c' escape sequence. 

If you are interested to see some extra details, you can run "make clean; make debug" and then run "./main.o" to see some 
extra output such as the programs "buffer" that stores the 6 most recently input digits, as well as the last keypress input.

## Explanation (lockengine)
The program itself is rather simple. It reads input directly from the terminal. When the program starts, it enables 'raw' input mode
so that each keypress is immediately sent to the program, rather than the user typing in a string of characters and hitting 'enter'. 
The user's keypresses are also not echoed back out to the terminal. 
It reads each keypress from the standard input, and if the character is not a digit it is quietly ignored (except for 'q' to quit).
The program uses a dynamic array (the 'vector' datatype) to store the 6 most recent digits. Once the array contains 6 digits, it compares
them to the pre-defined lock and unlock tokens. If the unlock sequence is detected, the program changes the 'state' variable
(which is just an integer that is 0 for locked and 1 for unlocked) and prints out "Unlocked!". Once the system is in the unlocked state, typing in 
the unlock sequence again does not do anything. Similarly, when the "lock" sequence is detected, the system checks the state to see if it is unlocked, 
and if it is it will change the 'state' variable back to 0 and print out "Locked!". 

## How-to (lockbreaker.o)
After compiling the source code with 'make', run './lockbreaker.o' in the terminal with an integer argument. For example, './lockbreaker.o 25'

The program will run the lockbreaker algorithm as many times as you specify in the argument, and it will print out the number of "guesses" (the number of randomly generated values)
it made until it guessed the correct unlock sequence. For each 'run', the program will average the guesses of each iteration as well as track the maximum and minimum number of guesses
for that 'run'. 

## Explanation (lockbreaker)
This program is arguably simpler than the other, it uses the same technique of filling a vector "buffer" with 6 digits and testing them against the correct unlock code. It tracks
the number of guesses with a simple 'counter' integer. After each iteration the counter value is compared against a running min and max value. It will collect all the counts 
into an array and use that array for calculating the overall average.