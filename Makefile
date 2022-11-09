# compiler to use 
CC = g++

CFLAGS = -g -Wall

debug: CFLAGS += -DDEBUG -g
debug: main

main: main.cpp
	$(CC) $(CFLAGS) -o main.o main.cpp

clean:
	rm *.o