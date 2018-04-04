#include <termbox.h>
#include "slakeio.h"
#include <stdlib.h>
#include <stdio.h>

int main(int argc, char *argv []) {
	(void)argc;
	(void)argv;

    
	// init log
	init_log();
    
    

	//main loop
	write_log("Call game_init\n");
	game_init();
	// -------- Test Slake --------
	write_log( "Init test slake\n");
	all_slakes = malloc(sizeof(struct slake_array_t));
	all_slakes->array = malloc(sizeof(struct slake_t) * 1);
	all_slakes->length = 1;
	my_slake = slake_init(&all_slakes->array[0], (double)(MAP_SIZE_X / 2), (double)(MAP_SIZE_Y / 2), 5, up, 0.1);
	
    	write_log("Start main loop\n");
	int loop = 1;
	
	while(loop) {
		struct tb_event e;
		tb_peek_event(&e, 100);
	
		switch (e.type) {
		case TB_EVENT_KEY:
			if (e.key == TB_KEY_ESC) {
                		write_log("ESC key detected\n");
				loop = 0;
			}
			else key_control(e.key);
		}
		// iterate over all slakes
		for (int i = 0; i < all_slakes->length; i++) {
			// move slake 
			slake_move(all_slakes->array);
			//checks slake ate and replaces 
			int ate_food = check_food(my_slake);
			replace_food(ate_food);
			// TODO: Check for food
		} 
		draw();
	}
	
	write_log("Call tb_shutdown\n");
	tb_shutdown();

	// end log and print 
	end_log(1);
	

	return 0;
}

