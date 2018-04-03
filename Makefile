CC = gcc
CFLAGS = -std=c11 -Wall -Wextra -pedantic -I${HOME}/.local/include -ltermbox -L${HOME}/.local/lib

main: tui.c slakeio.h slake.c control.c

tui: main.c tui.c

.PHONY: run_tui
run_tui: tui control
	env LD_LIBRARY_PATH=${HOME}/.local/lib ./tui

.PHONY: run
run: main
	env LD_LIBRARY_PATH=${HOME}/.local/lib ./main
