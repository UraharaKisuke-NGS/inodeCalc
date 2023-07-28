PROGRAM = inodeCalc
CC = gcc
CFLAGS = -O2 -lstdc++ -lm -Wall

#Build, and remove object files afterward.
all: $(PROGRAM) clean

clean:
	rm -f ./*.o
Inode.o: Inode.cpp Inode.hpp
	$(CC) $(CFLAGS) -c Inode.cpp
main.o: main.cpp Inode.hpp
	$(CC) $(CFLAGS) -c main.cpp
inodeCalc: Inode.o main.o
	$(CC) $(CFLAGS) -o inodeCalc Inode.o main.o
