#include <iostream>
#include <ctype.h>
#include <stdio.h>
#include <unistd.h>
#include <termios.h>
#include <stdlib.h>
#include <vector>
#include <string>
#include <stdint.h>
#include <inttypes.h>

using namespace std;
clock_t start,end;
double cpu_time;

int main(int argc, char** argv){
    if(argc < 2){
        printf("Requires argument: iterations\n");
        return -1;
    }

    int iterations = atoi(argv[1]);
    long long counter = 0;
    long long max;
    long long min;
    vector<char> buf;

    int array[iterations];
    
    srand(time(NULL));
    for(int i = 0; i < iterations; i++){
        while(1){
            int randomInt = (rand() % 10)+48; //generate a random integer between 48-57 (these correspond to 0-9 in ascii)
            char c = (char)randomInt;  	      //cast the integer to a character
            //printf("%c",c); //prints out all the characters guessed. uncomment at your own risk

            if(buf.size() < 5){               //grow the buffer if it has fewer than 5 items in it
				buf.push_back(c);
                counter++;
			}
			else{
				if(buf.size() >= 6) buf.erase(buf.begin()); //fill the buffer on the sixth inputted character. don't let the buffer exceed 6 items
				buf.push_back(c);
				string key(buf.begin(),buf.end());
                counter++;
				if(key == "607721")
				{
					printf("lock broken! It took %lld guesses to break the lock\n", counter);
                    if(i==0){
                        min = counter;
                        max = counter;
                    }
                    if(counter < min){
                        min = counter;
                    }
                    if(counter > max){
                        max = counter;
                    }
                    array[i] = counter;
                    counter = 0;
                    break;
				}
            }
        }
    }
    long long total = 0;
    for(int i = 0; i < iterations; i++){
        total += array[i]; 
    }
    long long average = total / iterations;

    printf("The average number of guesses was: %lld. The minimum was: %lld. The maximum was: %lld\n", average,min,max);

    int h = average/3600;
    int m = (average - (3600*h))/60;
    int s = average - (3600*h) - (60*m);
    printf("Given this average and an average of 1 second per keypress, it would take approximately %d hours, %d minutes and %d second to break the lock\n", h,m,s);
}
