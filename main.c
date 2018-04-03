#include <termbox.h>
#include "slakeio.h"
#include <stdlib.h>
#include <stdio.h>

void slakeio_log(char *str) {
	FILE *handle = fopen("./log", "a");
	fprintf(handle, str);
	fprintf(handle, "\n");
	fclose(handle);
}


int main(int argc, char *argv []) {
	(void)argc;
	(void)argv;
	//main loop
	tb_init();
	

	int loop = 1;
	while(loop) {
		struct tb_event e;
		tb_peek_event(&e, 100);
	
		switch (e.type) {
		case TB_EVENT_KEY:
			if (e.key == TB_KEY_ESC) {
				loop = 0;}
			else key_control(e.key);
		default:;
		}
		

	}

	tb_shutdown();
	return 0;
}
