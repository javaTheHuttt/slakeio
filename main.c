#include <termbox.h>
#include "slakeio.h"
#include <stdlib.h>
#include <stdio.h>

static const struct tb_cell empty = 
{
	.ch = ' ',
	.fg = TB_DEFAULT,
	.bg = TB_DEFAULT,
};

static const struct tb_cell myslake_player = 
{
	.ch = ' ',
	.fg = TB_DEFAULT,
	.bg = TB_GREEN,
};

static const struct tb_cell enemy_player =
{
	.ch = ' ',
	.fg = TB_DEFAULT,
	.bg = TB_RED,
};



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
<<<<<<< HEAD
		default: key_control(e.type);
	}
	}
=======
>>>>>>> 4c95d4a3eff2ba9bd6099742d23891803ee4892e
	tb_shutdown();
	return 0;
	}
}
