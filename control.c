// 
// Control (Keys etc.)
//

#include "slakeio.h"
#include <termbox.h>
#include <stdlib.h>
#include <stdio.h>
#include <time.h>
#include <math.h>

void init_food(void)
{
	
	for(int i = 0; i<300; i++)
	{
		struct slake_position_t food_cell = { .x = rand() % 1000, .y = rand() % 1000 };
		food[i] = food_cell;
	}
}

int check_food(struct slake_t *slake)
{
	for(int i = 0; i<300; i++)
	{
		if(slake->cells[0].x == food[i].x && slake->cells[0].y == food[i].y)
		{
			return i; //slake ate food 
			//TODO slake grows
			break;
		}
	}
	return (-1); //slake isst nichts -> MAP_END returnt

}

void replace_food(int place)
{
	if(place>=0) //(food[0].x != map->upper_left->x || food[0].y != map->upper_left->y)
	{
		food[place].x = rand() % 1000;
		food[place].y = rand() % 1000;
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
	
	map = malloc(sizeof(struct slake_map_t));
	map->upper_left = pos1;
	map->bottom_right = pos2;

	//food
	srand(time(NULL));	
	food = malloc(sizeof(struct slake_position_t)*300);
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
