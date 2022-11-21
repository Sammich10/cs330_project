#include <iostream>
#include <ctype.h>
#include <stdio.h>
#include <unistd.h>
#include <termios.h>
#include <stdlib.h>
#include <vector>
#include <string>
#define unlock_token "607721";
#define lock_token "607724";

using namespace std;
struct termios orig_termios;
bool locked = true;		//boolean value used to track the state of the locking engine

void disableRawMode(){
	tcsetattr(STDIN_FILENO, TCSAFLUSH, &orig_termios);//restore terminal attributes to their original values
}

//enable raw input mode in terminal so that our keyboard input is sent to the program immediately 
void enableRawMode(){
	tcgetattr(STDIN_FILENO,&orig_termios);//read terminal attributes into 'orig_termios' 
	atexit(disableRawMode);
	struct termios raw = orig_termios;//copy original terminal attr into 'raw'
	raw.c_lflag &= ~(ECHO | ICANON);//disable echoing in terminal (key presses wont be printed on screen) 
			       			//with a bitwise NOT, then a bitwise AND to set 4th bit to zero
							//also disables canonical mode so program reads byte by byte
	tcsetattr(STDIN_FILENO,TCSAFLUSH,&raw);//write terminal attributes
}

int unlockSequence(){		//this is the function that is called when the lock is unlocked, if this was a real implementation we would put 
	locked = false;				//code here to actually perform the unlocking of whatever mechanism it was deployed to control
	printf("Unlocked!\n");
	return 0;
}

int lockSequence(){
	locked = true;
	printf("Locked!\n");
	return 0;
}


int main(){
	enableRawMode();
	char c;
	vector<char> buf;
	
	while(read(STDIN_FILENO, &c, 1)==1 && c!='q'){ //read 1 byte from standard input until it is empty, exit on "q" input
		if(isdigit(c)){
			if(buf.size() < 5){
				buf.push_back(c);
			}
			else{
				if(buf.size() >= 6) buf.erase(buf.begin()); //dont let the buffer exceed 6 digits in size
				buf.push_back(c);							//add the newest keypress input to the back of the buffer
				string key(buf.begin(),buf.end());			//concatenate the buffer into a single string for comparison
				if(key == "607721")							//check to see if the correct unlock combination has been inputted 
				{
					if(locked == true){
						unlockSequence();
					}
				}
				if(key == "607724")							//check to see if the correct lock combination has been inputted
				{
					if(locked == false){
						lockSequence();
					}
				}
			}

			#ifdef DEBUG //print out extra information in debug mode
			printf("Current buffer: { ");
			for(auto i = buf.begin(); i != buf.end(); ++i){
				cout << *i << " ";
			}
			string s(buf.begin(),buf.end());
			printf("} \nLast keypress: ('%c')\n",c);
			cout << s << "\n";
			#endif

		}
	}
	disableRawMode();
	return 0;
}