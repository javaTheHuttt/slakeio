CC = gcc
CFLAGS = -std=c11 -Wall -Wextra -pedantic -I${HOME}/.local/include -ltermbox -L${HOME}/.local/lib -lm

main: tui.c slakeio.h slake.c control.c debug.c menu.c

tui: main.c tui.c control.c

.PHONY: run_tui
run_tui: tui 
	env LD_LIBRARY_PATH=${HOME}/.local/lib ./tui

.PHONY: run
run: main
	env LD_LIBRARY_PATH=${HOME}/.local/lib ./main
