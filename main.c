#include <termbox.h>
#include "slakeio.h"
#include <stdlib.h>
#include <stdio.h>

#define LOG_FILE ".log"     // log files in .gitignore: *.log

int main(int argc, char *argv []) {
	(void)argc;
	(void)argv;

    
    // log file
    slake_log = fopen(LOG_FILE, "w");     // clear 
    if (!slake_log) {
        perror("Unable to open log file! ");
        return 1;
    }
    

	//main loop
	tb_init();
	game_init();
	// -------- Test Slake --------
	all_slakes = malloc(sizeof(struct slake_array_t));
	all_slakes->array = malloc(sizeof(struct slake_t) * 1);

	fprintf(slake_log, "So weit so gut.\n");

	all_slakes->length = 1;
	my_slake = slake_init(&all_slakes->array[0], 0.0, 0.0, 5, up, 1.0);
	
	int loop = 1;
	
	while(loop) {
		struct tb_event e;
		tb_peek_event(&e, 100);
	
		switch (e.type) {
		case TB_EVENT_KEY:
			if (e.key == TB_KEY_ESC) {
				loop = 0;}
			else key_control(e.key);
		}
		// iterate over all slakes
		for (int i = 0; i < all_slakes->length; i++) {
			// move slake 
			slake_move(all_slakes->array);
			
			// TODO: Check for food
		} 
		draw();
	}

	tb_shutdown();
	return 0;
    
	// log stuff
	fclose(slake_log);  // close for writing
	slake_log = fopen(LOG_FILE, "r");   // open for reading
	char buf[1024];
	size_t bytes_read;
	while (!feof(slake_log)) {
	bytes_read = fread(buf, sizeof(buf[0]), sizeof(buf), slake_log);
	fwrite(buf, sizeof(buf[0]), bytes_read, stderr);
	}
	fclose(slake_log);

	return 0;

}

