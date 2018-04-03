#include <stdlib.h>
#include <time.h>
#include <math.h>

#include "slakeio.h"


void slake_move(struct slake_t *slake)
{
	// points to first position of slake head
	//struct slake_position_t *head = slake->cells;
	
	// current slake mode
	enum slake_mode_t mode = slake->mode;
	
	// expected distance since last move
	double delta_distance = slake->speed * slake->lastmove_clock;
	
	// storage management
	slake->cells = realloc(slake->cells, sizeof(struct slake_position_t) * slake->length);

	double old_head_x = slake->head_x;
	double old_head_y = slake->head_y;

	int x_diff = 0;
	int y_diff = 0;
	
	// new head positions
	if(mode == left) {
		slake->head_x = (slake->head_x) - delta_distance;
		x_diff = -1;
	}
	else if(mode == up) {
		slake->head_y = (head->y) + delta_distance;
		y_diff = -1;
	}
	else if(mode == right) {
		slake->head_x = slake->head_x + delta_distance;
		x_diff = 1;
	}
	else {	// down
		slake->head_y = slake->head_y - delta_distance;
		y_diff = 1;
	}
	
	// update clock after move
	slake->lastmove_clock = clock();

	int head_delta_distance_x = (int)(round(old_head_x)-round(slake->head_x));
	int head_delta_distance_y = (int)(round(old_head_y)-round(slake->head_y));
	for (int i = 0; i < abs(head_delta_distance_x) + abs(head_delta_distance_y); i++) {
		
		// move slake tail  
		for (int i = 1; i < slake->length; ++i) {
			slake->cells[i] = slake->cells[i-1];
		}

		// move head
		slake->cells[0].x += x_diff;
		slake->cells[0].y += y_diff;
	}
}

