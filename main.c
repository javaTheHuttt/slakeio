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
	game_init();
	// -------- Test Slake --------
	struct slake_position_t position;
	position.x = 0;
	position.y = 0;
	 
	my_slake = slake_init(position, 5, up, 1);
	all_slakes = malloc(sizeof(struct slake_array_t) * 5);   // ! MAX 5 SLAKES !
	all_slakes[0] = my_slake;
	
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

