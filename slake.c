#include <stdlib.h>
#include <math.h>

#include "slakeio.h"

void slake_move(struct slake_t *slake)
{
	// points to first position of slake head
	//struct slake_position_t *head = slake->cells;
	
	// current slake mode
	enum slake_mode_t mode = slake->mode;

	double current_time = get_time();
	
	// expected distance since last move
	double delta_distance = slake->speed * (current_time - slake->lastmove_clock);

	// update clock after move
	slake->lastmove_clock = current_time;
	
	// storage management
	if (slake->old_length != slake->length) {
		slake->cells = realloc(slake->cells, sizeof(struct slake_position_t) * slake->length);
		slake->old_length = slake->length;
	}

	double old_head_x = slake->head_x;
	double old_head_y = slake->head_y;

	int x_diff = 0;
	int y_diff = 0;
	
	// check if head will be outside map 
	if (!in_rect(map, &slake->cells[0])) {
		status = lost_status;
	}
	// check if inside other snake
//	for(int s = 0; s < all_slakes->length; s++) {
//		// go with c through all cells of the slake
//		int start_index = 0;
//		if(&all_slakes->array[s] == slake) {
//			start_index = 1;
//		}
//		for (int c = start_index; c < (all_slakes->array[s]).length; c++) {
//			if (slake->cells[0].x == all_slakes->array[s].cells[c].x &&
//				slake->cells[0].x == all_slakes->array[s].cells[c].x) {
//				status = lost_status;
//				return;
//			}
//		}
//	}


	for(int i = 2; i<my_slake->length; i++)
	{
		if(my_slake->cells[0].x == my_slake->cells[i].x && my_slake->cells[0].y == my_slake->cells[i].y)
		{
			status = lost_status;
			write_log("Slake got killed at x=%d, y=%d\n", my_slake->cells[0].x, my_slake->cells[0].y);
			return;
		}
	}


	// new head positions
	if(mode == left) {
		slake->head_x -= delta_distance;
		x_diff = -1;
	}
	else if(mode == up) {
		slake->head_y += delta_distance;
		y_diff = -1;
	}
	else if(mode == right) {
		slake->head_x += delta_distance;
		x_diff = 1;
	}
	else {	// down
		slake->head_y -= delta_distance;
		y_diff = 1;
	}
	

	int head_delta_distance_x = abs((int) (round(old_head_x)-round(slake->head_x)));
	int head_delta_distance_y = abs((int) (round(old_head_y)-round(slake->head_y)));
	
	write_log("%f %f %f\n", delta_distance, old_head_x, slake->head_x);
	write_log("Delta distance x: %d\n", head_delta_distance_x);		
	write_log("Delta distance y: %d\n", head_delta_distance_y);
		
	for (int i = 0; i < head_delta_distance_x + head_delta_distance_y; i++) {
		
		// move head
		slake->cells[0].x += x_diff;
		slake->cells[0].y += y_diff;
	
		write_log("Tail position: \n");
		// move slake tail  		
		for (int i = (slake->length - 1); i > 0; i--) {
			write_log("	Cell %d:\n", i);
			slake->cells[i] = slake->cells[i-1];	
			write_log("		x: %d\n", slake->cells[i].x);
			write_log("		y: %d\n", slake->cells[i].y);
		}
		write_log("\n");
	}
}


struct slake_t *slake_init(struct slake_t *slake, double head_x, double head_y, 
	int length, enum slake_mode_t mode, double speed)
{
	
	// from arguments
	slake->head_x = head_x;
	slake->head_y = head_y;

	slake->length = length;
	slake->old_length = length;

	slake->mode = mode;
	slake->speed = speed;
	
	// position
	slake->cells = malloc(sizeof(struct slake_position_t) * length);
	
	write_log("Generate slake: \n");
	struct slake_position_t temp_position;
	for (int i = 0; i < length; i++) {
		write_log("     Cell %d:\n", i);
		temp_position.x = (int) head_x;
		temp_position.y = (int) head_y + i; 
		slake->cells[i] = temp_position;
		write_log("             x: %d\n", slake->cells[i].x);
 		write_log("             y: %d\n", slake->cells[i].y);
	} 
	
	slake->lastmove_clock = get_time();
	
	return slake;

}

