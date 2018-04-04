#include <termbox.h>
#include "slakeio.h"
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

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


static const struct tb_cell tb_food =
{
	.ch = '#',
	.fg = TB_BOLD,
	.bg = TB_BLUE,
};

static const struct tb_cell map_border =
{
	.ch = '#',
	.fg = TB_BOLD,
	.bg = TB_WHITE,
};

void init_tui(void) {
	int tbe = tb_init();
	if (tbe < 0) {printf("tb error %d", tbe);exit(1);}
	tbw = tb_width();
	tbh = tb_height();
	
}

struct slake_map_t *get_screen(void) {
	// write_log("Slake Position\n x: %d\n y: %d\n", my_slake->cells[0].x, my_slake->cells[0].y);
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

void show_coordinates(int x, int y) {
	char *str = malloc(sizeof(char) *20);
	int len = 14;
	sprintf(str, "x: %d, y: %d", x, y);
	static struct tb_cell text =
		{
			.fg = TB_BOLD,
			.bg = TB_WHITE,
		};
	for(int i = 0; i < len; i++) {
		text.ch = str[i];
		tb_put_cell(i, 0, &text);
	}
	
}



void draw(void) {
	// ################## DRAW SLAKES #########################
	struct slake_map_t *screen = get_screen();
	// go with s through all slakes

	
	int x;
	int y;
	
	//write_log("Screen Position\n upper_left:\n  x: %d\n  y: %d\n\n bottom_right: \n  x: %d\n  y: %d\n", screen->upper_left->x, screen->upper_left->y, screen->bottom_right->x, screen->bottom_right->y);

	tb_clear();
	for(int s = 0; s < all_slakes->length; s++) {
		// go with c through all cells of the slake
		for (int c = 0; c < (all_slakes->array[s]).length; c++) {
			if (in_rect(screen, &(all_slakes->array[s]).cells[c])) {
				x = ((all_slakes->array[s]).cells[c]).x - screen->upper_left->x;
				y = ((all_slakes->array[s]).cells[c]).y - screen->upper_left->y;
				tb_put_cell(x, y, &myslake_player);
				
			}
	
		}
	}
	// ################ SHOW COORDINATES ######################
	show_coordinates(my_slake->cells[0].x, my_slake->cells[0].y);



	// ####################### DRAW FOOD ########################
	
	
	for (int i = 0;i<300;i++) {
		if(in_rect(screen, &food[i])) {
			x = food[i].x - screen->upper_left->x;
			y = food[i].y - screen->upper_left->y;
			tb_put_cell(x, y, &tb_food);
		}
	};

	// ################# DRAW MAP BORDERS #####################
	if ((! in_rect(map, screen->upper_left))) {
		for(int x = 0;x <= (screen->upper_left->x - map->upper_left->x); x++) {
			for(int y = 0; y <= (screen->upper_left->y - map->upper_left->y); y++) {
				tb_put_cell(x, y, &map_border);
			}
		}
	}
	else if ((!in_rect(map, screen->bottom_right))) {
		for(int x = screen->bottom_right->x - map->bottom_right->x; x >= 0; x--) {
			for(int y = screen->bottom_right->y - map->bottom_right->y; y >= 0; y--) {
				tb_put_cell(x, y, &map_border);
			}
		}
	}
	
	tb_present();	

}
