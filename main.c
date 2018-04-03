#include <termbox.h>
#include "slakeio.h"
#include <stdlib.h>
#include <stdio.h>



int main(int argc, char *argv []) {
	(void)argc;
	(void)argv;
	//main loop
	tb_init();
	
	while(1) {
		struct tb_event e;
		tb_peek_event(&e, 100);
	
		switch (e.type) {
		case TB_EVENT_KEY:
			if (e.key == TB_KEY_ESC) {
				break;
			}
		}
	tb_shutdown();
	return 0;
	}
}
