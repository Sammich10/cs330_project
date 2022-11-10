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


int main(){
	enableRawMode();
	char c;
	vector<char> buf;
	int state = 0; //state represents the state of the system, 0 for 'locked', 1 for 'unlocked'
	
	while(read(STDIN_FILENO, &c, 1)==1 && c!='q'){ //read 1 byte from standard input until it is empty, exit on "q" input
		if(isdigit(c)){
			if(buf.size() < 6){
				buf.push_back(c);
			}
			else{
				buf.erase(buf.begin());
				buf.push_back(c);
				string key(buf.begin(),buf.end());
				if(key == "607721")
				{
					if(state == 0){
						state = 1;
						printf("Unlocked!\n");
					}
				}
				if(key == "607724")
				{
					if(state == 1){
						state = 0;
						printf("Locked!\n");
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