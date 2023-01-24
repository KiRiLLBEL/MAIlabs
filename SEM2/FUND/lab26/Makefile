CC = gcc
LD = gcc
CCFLAGS = -g -Wall -pedantic -std=c99
LDFLAGS =
OBJ = main.o vector.o stack.o queue.o deque.o
HDR = vector.h stack.h deque.h queue.h
all: $(OBJ)
	@$(LD) $(LDFLAGS) -o main $(OBJ)
main.o: main.c $(HDR)
	@$(CC) $(CCFLAGS) -c main.c
vector.o: vector.c vector.h
	@$(CC) $(CCFLAGS) -c vector.c
queue.o: queue.c queue.h
	@$(CC) $(CCFLAGS) -c queue.c
stack.o: stack.c stack.h
	@$(CC) $(CCFLAGS) -c stack.c
deque.o: deque.c deque.h
	@$(CC) $(CCFLAGS) -c deque.c
clean:
	@rm -f *.o main

