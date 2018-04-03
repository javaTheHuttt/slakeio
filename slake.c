#include <stdlib.h>
#include <time.h>
#include "slakeio.h"

void slake_move(struct slake_t *slake)
{
	// points to first position of slake head
	struct slake_position_t *head = slake->cells;
	
	// current slake mode
	enum slake_mode_t mode = slake->mode;
	
	// expected distance since last move
	double delta_distance = slake->speed * slake->lastmove_clock;
	
	// storage management
	head = realloc(head, sizeof(struct slake_position_t) * slake->length);
		
	// new head positions
	if(mode == left) {
		head->x = (head->x) - delta_distance;
		head->y = (head->y);
	}
	else if(mode == up) {
		head->x = head->x;
		head->y = (head->y) + delta_distance;
	}
	else if(mode == right) {
		head->x = (head->x) + delta_distance;
		head->y = head->y;
	}
	else {	// down
		head->x = head->x;
		head->y = (head->y) - delta_distance;
	}
	
	// move slake tail  
	for(int i = 1; i < slake->length; ++i) {
		slake->cells[i] = slake->cells[i-1];
	}
	
	// update clock after move
	slake->lastmove_clock = clock();
}

