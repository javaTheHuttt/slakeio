CC = gcc
CFLAGS = -std=c11 -Wall -Wextra -pedantic

main: termbox.c
	$(CC) $(CFALGS) $^ -o $@
