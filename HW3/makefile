CC=gcc
CCLINK=$(CC)
CFLAGS=-g -Wall -std=c99
OBJS=student.o stack.o main.o
EXEC=prog.exe
RM=./*.o ./*.exe

$(EXEC): $(OBJS)
	$(CCLINK) $(OBJS) -o $(EXEC)

student.o: student.h student.c
	$(CC) $(CFLAGS) -c student.c

stack.o: stack.h stack.c
	$(CC) $(CFLAGS) -c stack.c

main.o: main.c student.h stack.h
	$(CC) $(CFLAGS) -c main.c

clean:
	rm -rf $(RM)