#include <iostream>
#include <ctype.h>
#include <stdio.h>
#include <unistd.h>
#include <termios.h>
#include <stdlib.h>
//enable raw input mode in terminal so that our keyboard input is sent to the program immediately 

struct termios orig_termios;

void disableRawMode(){
	tcsetattr(STDIN_FILENO, TCSAFLUSH, &orig_termios);//restore terminal attributes to their original values
}

void enableRawMode(){
	tcgetattr(STDIN_FILENO,&orig_termios);//read terminal attributes into 'orig_termios' 
	atexit(disableRawMode);
	struct termios raw = orig_termios;//copy original terminal attr into 'raw'
	raw.c_lflag &= ~(ECHO | ICANON);//disable echoing in terminal (key presses wont be printed on screen) 
			       		//with a bitwise NOT, then a bitwise AND to set 4th bit to zero
					//also disables canonical mode so program reads byte by byte
	tcsetattr(STDIN_FILENO,TCSAFLUSH,&raw);//write terminal attricbutes
}


int main(){
	enableRawMode();
	char c;
	//read 1 byte from standard input until it is empty, exit on "q" input
	while(read(STDIN_FILENO, &c, 1)==1 && c!='q'){
		if(iscntrl(c)){
			printf("%d\n",c);
		}else{
			printf("%d, ('%c')\n",c,c);
		}
	}
	disableRawMode();
	return 0;
}