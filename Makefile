# @file Makefile
# Řešení IJC-DU1, příklad a), b), 24.3.2025
# Autor: Radim Kopunec (xkopunr00), FIT

CC = gcc #-m32
CFLAGS = -g -std=c11 -Wall -Wextra -Werror -pedantic -O2 #-O0 -Winline #-fsanitize=address
LDFLAGS = -lm #-fsanitize=address

OBJ_P = primes.o eratosthenes.o error.o
OBJ_PI = primes-i.o eratosthenes-i.o error.o
OBJ_SD = steg-decode.o ppm.o eratosthenes-i.o error.o utf8_check.o

EXEC_P = primes
EXEC_PI = primes-i
EXEC_SD = steg-decode

PPM_PIC = du1-obrazek.ppm

.PHONY: all valgrind-p valgrind-pi valgrind-sd clean

all: $(EXEC_P) $(EXEC_PI) $(EXEC_SD)

$(EXEC_P): $(OBJ_P)
	$(CC) $(CFLAGS) $(OBJ_P) -o $(EXEC_P) $(LDFLAGS)

$(EXEC_PI): $(OBJ_PI)
	$(CC) $(CFLAGS) $(OBJ_PI) -o $(EXEC_PI) $(LDFLAGS)

$(EXEC_SD): $(OBJ_SD)
	$(CC) $(CFLAGS) $(OBJ_SD) -o $(EXEC_SD) $(LDFLAGS)

eratosthenes.o: eratosthenes.c eratosthenes.h bitset.h error.h
	$(CC) $(CFLAGS) -c eratosthenes.c -o eratosthenes.o

eratosthenes-i.o: eratosthenes.c eratosthenes.h bitset.h error.h
	$(CC) -DUSE_INLINE $(CFLAGS) -c eratosthenes.c -o eratosthenes-i.o

error.o: error.c error.h
	$(CC) $(CFLAGS) -c error.c -o error.o

ppm.o: ppm.c ppm.h error.h
	$(CC) -DUSE_INLINE $(CFLAGS) -c ppm.c -o ppm.o

primes.o: primes.c bitset.h error.h eratosthenes.h
	$(CC) $(CFLAGS) -c primes.c -o primes.o

primes-i.o: primes.c bitset.h error.h eratosthenes.h
	$(CC) -DUSE_INLINE $(CFLAGS) -c primes.c -o primes-i.o

steg-decode.o: steg-decode.c ppm.h bitset.h error.h eratosthenes.h utf8_check.h
	$(CC) -DUSE_INLINE $(CFLAGS) -c steg-decode.c -o steg-decode.o

utf8_check.o: utf8_check.c
	$(CC) $(CFLAGS) -c $^

valgrind-p: $(EXEC_P)
	valgrind --main-stacksize=67108864 --leak-check=full --track-origins=yes ./$(EXEC_P)

valgrind-pi: $(EXEC_PI)
	valgrind --main-stacksize=67108864 --leak-check=full --track-origins=yes ./$(EXEC_PI)

valgrind-sd: $(EXEC_SD)
	valgrind --leak-check=full --track-origins=yes ./$(EXEC_SD) $(PPM_PIC)

run: $(EXEC_P) $(EXEC_PI)
	ulimit -s unlimited && ./$(EXEC_P)
	ulimit -s unlimited && ./$(EXEC_PI)

zip: *.c *.h Makefile
	zip xkopunr00.zip *.c *.h Makefile

clean:
	rm -f $(EXEC_P) $(EXEC_PI) $(EXEC_SD) *.o *.gch
