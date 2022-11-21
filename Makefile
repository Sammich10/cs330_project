# compiler to use 
CC = g++

CFLAGS = -g -Wall

main: lockengine.cpp lockbreaker.cpp
	$(CC) $(CFLAGS) -o lockengine.o lockengine.cpp
	$(CC) $(CFLAGS) -o lockbreaker.o lockbreaker.cpp

debug: CFLAGS += -DDEBUG -g
debug: main

clean:
	rm *.o