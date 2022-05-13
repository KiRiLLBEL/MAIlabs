CC = gcc 
CFLAGS = -g -Wall -Wextra -pedantic -std=c99 -w -pipe -O3 -lm

lab24:  lexer.o tree.o transform.o main.o
	$(CC) $^ -o $@ $(CFLAGS)

clean:
	rm -f *.o lab24 
