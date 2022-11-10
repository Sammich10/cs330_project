# CS330 Coding Assignment

## How-to (main)
Do use this program, ensure you have C/C++ and G++ compiler installed on your system.
This program was created and tested on Ubuntu 22.04.1 LTS using Vim and VSCode. It relies primarily 
on C code and uses a little bit of C++, mainly just for the 'vector' datatype (a dynamic array). 

To run the program, clone the repository, and navigate to the directory you cloned it in using the 
Ubuntu terminal emulator. Type and run "make" to compile the program. Then simply run "./main.o".
You may then start to type in digits. When the correct unlock sequence is typed in, the program will print "Unlocked!",
and likewise when the lock sequence is typed in, it will print "Locked!". 

To exit the program, either type the character 'q' or use the 'ctrl+c' escape sequence. 

If you are interested to see some extra details, you can run "make clean; make debug" and then run "./main.o" to see some 
extra output such as the programs "buffer" that stores the 6 most recently input digits, as well as the last keypress input.

## Explanation (main)
The program itself is rather simple. It reads input directly from the terminal. When the program starts, it enables 'raw' input mode
so that each keypress is immediately sent to the program, rather than the user typing in a string of characters and hitting 'enter'. 
It reads each keypress from the standard input, and if the character is not a digit it is quietly ignored (except for 'q' to quit).
The program uses a dynamic array (the 'vector' datatype) to store the 6 most recent digits. Once the array contains 6 digits, it compares
them to the pre-defined lock and unlock tokens. If the unlock sequence is detected, the program changes the 'state' variable
(which is just an integer that is 0 for locked and 1 for unlocked) and prints out "Unlocked!". Once the system is in the unlocked state, typing in 
the unlock sequence again does not do anything. Similarly, when the "lock" sequence is detected, the system checks the state to see if it is unlocked, 
and if it is it will change the 'state' variable back to 0 and print out "Locked!". 
