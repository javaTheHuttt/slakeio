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


void init_tui(void) {
	int tbe = tb_init();
	if (tbe < 0) {printf("tb error %d", tbe);exit(1);}
	tbw = tb_width();
	tbh = tb_height();
	
}

struct slake_map_t *get_screen(void) {
	//screen center shoudl be the position of the head of the slake
	struct slake_position_t *screen_center = &(my_slake->cells[0]);
	struct slake_position_t *screencorner_upper_left = 
				malloc(sizeof(struct slake_position_t));
	
	screencorner_upper_left->x = screen_center->x - (tbw / 2) - (tbw % 2) + 1;
	screencorner_upper_left->y = screen_center->y - (tbh / 2) - (tbh % 2) + 1;
	


	struct slake_position_t *screencorner_bottom_right = 
				malloc(sizeof(struct slake_position_t));

	screencorner_bottom_right->x = screen_center->x + (tbw / 2);
	screencorner_bottom_right->y = screen_center->y + (tbh / 2);
	
	struct slake_map_t *screen = malloc(sizeof(struct slake_map_t));
	screen->upper_left = screencorner_upper_left;
	screen->bottom_right = screencorner_bottom_right;
	return screen;
}



void draw(void) {
	struct slake_map_t *screen = get_screen();
	// go with s through all slakes
	int x;
	int y;


	tb_clear();
	for(int s = 0; s < all_slakes->length; s++) {
		// go with c through all cells of the slake
		for (int c = 0; c < (all_slakes->array[s]).length; c++) {
			//all_slakes->array[s]).cells[c]
			
			if (in_rect(screen, &(all_slakes->array[s]).cells[c])) {
				x = ((all_slakes->array[s]).cells[c]).x - screen->upper_left->x;
				y = ((all_slakes->array[s]).cells[c]).y - screen->upper_left->y;
				tb_put_cell(x, y, &myslake_player);
			}
	
		}
	}
	
	tb_present();	

}
