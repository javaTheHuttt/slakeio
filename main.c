#include <termbox.h>
#include "slakeio.h"
#include <stdlib.h>
#include <stdio.h>

int main(int argc, char *argv []) {
	(void)argc;
	(void)argv;

    
	// init log
	init_log();
	game_init();
	init_tui();	
    	write_log("Start main loop\n");
	loop = 1;
	startmenu();	
	while(loop) {
		if(status == win_status) { win(); }
		else if(status == lost_status) { lost(); }
		else if(status == playing_status)
			{
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
			} 
			draw();
		}
	}
	
	write_log("Call tb_shutdown\n");
	tb_shutdown();

	// end log and print 
	end_log(1);
	

	return 0;
}


void game_uninit(void) {
	free(all_slakes->array);
	free(all_slakes);
}
