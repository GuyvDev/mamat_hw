CC=gcc
CCLINK=$(CC)
CFLAGS=-g -Wall -std=c99
RM=./grades.o ./libgrades.so

libgrades.so: grades.o
	$(CCLINK) -shared grades.o -o libgrades.so -llinked-list -L.

grades.o: grades.c grades.h
	$(CC) $(CFLAGS) -c -fpic grades.c

clean:
	rm -rf $(RM)