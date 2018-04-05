// 
// Control (Keys etc.)
//

#include "slakeio.h"
#include <termbox.h>
#include <stdlib.h>
#include <stdio.h>
#include <time.h>
#include <math.h>
#include <sys/time.h>

//init 300 random food-coordinates
void init_food(void)
{
	
	for(int i = 0; i<AMOUNT_BIG_FOOD; i++)
	{
		struct slake_position_t big_food_cell = { .x = rand() % MAP_SIZE_X, .y = rand() % MAP_SIZE_Y };
		big_food[i] = big_food_cell;
	}

	for(int i = 0; i<AMOUNT_SMALL_FOOD; i++)
	{
		struct slake_position_t small_food_cell = { .x = rand() % MAP_SIZE_X, .y = rand() % MAP_SIZE_Y };
		small_food[i] = small_food_cell;
	}
}

//checks if slake ate food
int check_food(struct slake_t *slake)
{
	//checks big_food
	for(int i = 0; i< AMOUNT_BIG_FOOD; i++)
	{
		if(slake->cells[0].x == big_food[i].x && slake->cells[0].y == big_food[i].y)
		{
			slake->length+=3;
			return i; //slake ate food 
		
			break;
		}
	}
	//checks small_food
	for(int j = 0; j<AMOUNT_SMALL_FOOD; j++)
	{
		if(slake->cells[0].x == small_food[j].x && slake->cells[0].y == small_food[j].y)
		{
			slake->length++;
			return j; //slake ate food 
		
			break;
		}
	}
	return (-1); //slake ate nothing

}

//if slake ate food this functions creats new food-coordinate
void replace_food(int place)
{
	if(/*place>=0 &&*/ my_slake->length-my_slake->old_length>1)
	{
		big_food[place].x = rand() % MAP_SIZE_X;
		big_food[place].y = rand() % MAP_SIZE_Y;
	}
	else if(place>=0)
	{
		small_food[place].x = rand() % MAP_SIZE_X;
		small_food[place].y = rand() % MAP_SIZE_Y;
	}
}


void game_init(void) {
	//initialize map
	struct slake_position_t *pos1 = malloc(sizeof(struct slake_position_t)); 
	pos1->x = 0;
	pos1->y = 0;
	struct slake_position_t *pos2 = malloc(sizeof(struct slake_position_t)); 

	//size of the map
	pos2->x = MAP_SIZE_X;
	pos2->y = MAP_SIZE_Y;
	
	map = malloc(sizeof(struct slake_map_t));
	map->upper_left = pos1;
	map->bottom_right = pos2;
	//init slakes

	write_log("Init test slake\n");
	all_slakes = malloc(sizeof(struct slake_array_t)*1);
	all_slakes->array = malloc(sizeof(struct slake_t)*1);
	all_slakes->length = 1;
	my_slake = slake_init(&all_slakes->array[0], (double)(MAP_SIZE_X / 2), (double)(MAP_SIZE_Y /2),5, up, 10);

	//initialize food
	srand(time(NULL));	
	big_food = malloc(sizeof(struct slake_position_t)*AMOUNT_BIG_FOOD);
	small_food = malloc(sizeof(struct slake_position_t)*AMOUNT_SMALL_FOOD);
	init_food();



}

//handles key-input
void key_control(uint16_t key)
{
 	enum slake_mode_t old_mode = my_slake->mode; //mode right before a change
	// checks if mode-change is possible
	if((old_mode == left && key == TB_KEY_ARROW_RIGHT) || (old_mode == left && key == TB_KEY_ARROW_LEFT)){goto end;}
 	if((old_mode == right && key == TB_KEY_ARROW_LEFT) || (old_mode == right && key == TB_KEY_ARROW_RIGHT)){goto end;}
	if((old_mode == up && key == TB_KEY_ARROW_DOWN) || (old_mode == up && key == TB_KEY_ARROW_UP)){goto end;}
	if((old_mode == down && key == TB_KEY_ARROW_UP) || (old_mode == down && key == TB_KEY_ARROW_DOWN)){goto end;}
	// changes mode
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

double get_time(void) {
	struct timeval time;
	gettimeofday(&time, NULL);
	return (double)time.tv_sec + (double)time.tv_usec / 1000000;
}
