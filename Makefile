CC=gcc
CFLAGS=-Wall -Wextra -std=c11

all:
	$(CC) $(CFLAGS) main.c -o calc

clean:
	rm -f calc out out.s
