// 
// Control (Keys etc.)
//

#include "slakeio.h"
#include "termbox.h"

static enum slake_mode key_control(e.type)
{
	if(e.type == TB_KEY_LEFT) {  *my_slake->slake_mode =left; }	
	if(e.type == TB_KEY_UP) { *my_slake->slake_mode =up; }
	if(e.type == TB_KEY_RIGHT) { *my_slake->slake_mode =right; }
	if(e.type == TB_KEY_DOWN) { *my_slake->slake_mode =down; }
	}
}


void log(char *str) {
	FILE handle = fopen("./log", "a");
	
}
