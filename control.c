// 
// Control (Keys etc.)
//

#include "slakeio.h"
#include <termbox.h>

void key_control(uint16_t key)
{
 	enum old_mode = *my_slake->slake_mode; //mode right before a change
	// 	checks that modechange is possible
	if(oldmode == TB_KEY_LEFT && e.type == TB_KEY_RIGHT);
 	if(oldmode == TB_KEY_RIGHT && e.type == TB_KEY_LEFT);
	if(oldmode == TB_KEY_UP && e.type == TB_KEY_DOWN);
	if(oldmode == TB_KEY_DOWN && e.type == TB_KEY_UP);
	//	changes mode
	if(e.type == TB_KEY_LEFT) { *my_slake->slake_mode =left; }	
	if(e.type == TB_KEY_UP) { *my_slake->slake_mode =up; }
	if(e.type == TB_KEY_RIGHT) { *my_slake->slake_mode =right; }
	if(e.type == TB_KEY_DOWN) { *my_slake->slake_mode =down; }
	}
}


void slakeio_log(char *str) {
	FILE *handle = fopen("./log", "a");
	fprintf(handle, str);
	fprintf(handle, "\n");
	fclose(handle);
}
