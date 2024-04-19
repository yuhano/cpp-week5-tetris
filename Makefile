FLAGS = -Werror -std=c++11 -g
LINKER_FLAGS = $(FLAGS)
CC = g++

ifneq ($(OS),Windows_NT)
	LINKER_FLAGS += -lncurses
endif

all: main

main: main.o game.o tetromino.o console.o timer.o display.o board.o
	$(CC) $(LINKER_FLAGS) -o main main.o game.o tetromino.o console.o timer.o display.o board.o

console.o: console/console.cpp console/console.h
	$(CC) $(FLAGS) -c -o console.o console/console.cpp

main.o: main.cpp game.h tetromino.h
	$(CC) $(FLAGS) -c -o main.o main.cpp

game.o: game.cpp game.h tetromino.h
	$(CC) $(FLAGS) -c -o game.o game.cpp

tetromino.o: tetromino.cpp tetromino.h
	$(CC) $(FLAGS) -c -o tetromino.o tetromino.cpp

timer.o: timer.cpp timer.h
	$(CC) $(FLAGS) -c -o timer.o timer.cpp

display.o: display.cpp display.h
	$(CC) $(FLAGS) -c -o display.o display.cpp

board.o: board.cpp board.h
	$(CC) $(FLAGS) -c -o board.o board.cpp

clean:
	del /Q *.o
	del /Q *.exe

