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
	
	// -------- Test Slake --------
	my_slake = slake_init(0.0, 0.0, 5, up, 1.0);
	all_slakes = malloc(sizeof(struct slake_array_t) * 5);   // ! MAX 5 SLAKES !
	all_slakes->array = my_slake;
	all_slakes->length = 1;
	
	int loop = 1;
	while(loop) {
		struct tb_event e;
		tb_peek_event(&e, 100);
	
		switch (e.type) {
		case TB_EVENT_KEY:
			if (e.key == TB_KEY_ESC) {
				loop = 0;
			}

		default: key_control(e.key);

		}
		
		// iterate over all slakes
		for (int i = 0; i < all_slakes->length; i++) {
			// move slake 
			slake_move(all_slakes->array);
			
			// TODO: Check for food
		} 
	}

	tb_shutdown();
	return 0;
}

