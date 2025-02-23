CC = gcc
CFLAGS = -Wall -Wextra -std=c11
OBJ = main.o NumberstoLetters.o cache.o

main: $(OBJ)
	$(CC) $(CFLAGS) -o main $(OBJ)

main.o: main.c NumberstoLetters.h cache.h
	$(CC) $(CFLAGS) -c main.c

NumberstoLetters.o: NumberstoLetters.c NumberstoLetters.h cache.h
	$(CC) $(CFLAGS) -c NumberstoLetters.c

cache.o: cache.c cache.h
	$(CC) $(CFLAGS) -c cache.c

clean:
	rm -f *.o main
