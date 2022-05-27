CC = gcc
CFLAGS = -Wall -Wextra -g -std=c99 -O3

symbolic:	mystring.o token.o lexer.o expression.o parser.o printer.o transform.o main.o
	$(CC) $^ -o $@

.c.o:
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -f symbolic *.o
