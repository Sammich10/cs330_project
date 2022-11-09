# compiler to use 
CC = g++

CFLAGS = -g -Wall

main: main.cpp
	$(CC) $(CFLAGS) -o main.o main.cpp

debug: CFLAGS += -DDEBUG -g
debug: main

clean:
	rm *.o