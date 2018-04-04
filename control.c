// 
// Control (Keys etc.)
//

#include "slakeio.h"
#include <termbox.h>
#include <stdlib.h>
#include <stdio.h>
#include <time.h>

void rand_food_pos(void)
{
	
	for(int i = 0; i<300; i++)
	{
		food[i].x = rand() % 1000;
		food[i].y = rand() % 1000;
	}
}

struct slake_position_t check_food(struct slake_position_t *head)
{
	for(int i = 0; i<300; i++)
	{
		if( head[0].x == food[i].x && head[0].y == food[i].y)
		{
			return food[i]; //slake ate food 
			//TODO slake grows
			break;
		}
	}
	struct slake_position_t end;
	end.x = MAP_SIZE_X;
	end.y = MAP_SIZE_Y;	
	return end; //slake isst nichts -> MAP_END returnt

}

void init_food(void)
{
	for(int i = 0; i<300; i++)
	{
		tb_change_cell('+', TB_RED, TB_DEFAULT, food[i].x, food[i].y);
	}
}

void game_init(void) {
	//initialize map
	struct slake_position_t *pos1 = malloc(sizeof(struct slake_position_t)); 
	pos1->x = 0;
	pos1->y = 0;
	struct slake_position_t *pos2 = malloc(sizeof(struct slake_position_t)); 

	//size of the map
	pos2->x = 1000;
	pos2->y = 1000;
	
	struct slake_map_t *map = malloc(sizeof(struct slake_map_t));
	map->upper_left = pos1;
	map->bottom_right = pos2;

	//food
	srand(time(NULL));	
	food = malloc(sizeof(struct slake_position_t)*300);
	rand_food_pos();
	init_food();
	
	init_tui();


}
void key_control(uint16_t key)
{
 	enum slake_mode_t old_mode = my_slake->mode; //mode right before a change
	// 	checks that modechange is possible
	if((old_mode == left && key == TB_KEY_ARROW_RIGHT) || (old_mode == left && key == TB_KEY_ARROW_LEFT)){goto end;}
 	if((old_mode == right && key == TB_KEY_ARROW_LEFT) || (old_mode == right && key == TB_KEY_ARROW_RIGHT)){goto end;}
	if((old_mode == up && key == TB_KEY_ARROW_DOWN) || (old_mode == up && key == TB_KEY_ARROW_UP)){goto end;}
	if((old_mode == down && key == TB_KEY_ARROW_UP) || (old_mode == down && key == TB_KEY_ARROW_DOWN)){goto end;}
	//	changes mode
	if(key == TB_KEY_ARROW_LEFT) { my_slake->mode =left; }	
	if(key == TB_KEY_ARROW_UP) { my_slake->mode =up; }
	if(key == TB_KEY_ARROW_RIGHT) { my_slake->mode =right; }
	if(key == TB_KEY_ARROW_DOWN) { my_slake->mode =down; }
	end:;
}



int in_rect(struct slake_map_t *rect, struct slake_position_t *pos) {
	if ((pos->x > rect->upper_left->x) && 
		(pos->y > rect->upper_left->y) &&
		(pos->x < rect->bottom_right->x) &&
		(pos->y < rect->bottom_right->y)) {
			return 1;
		}
	return 0;
}
