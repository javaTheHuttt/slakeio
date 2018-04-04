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
	double delta_distance = slake->speed * slake->lastmove_clock / 10000;
	
	// storage management
	// TODO: Update other pointers?
	slake->cells = realloc(slake->cells, sizeof(struct slake_position_t) * slake->length);

	double old_head_x = slake->head_x;
	double old_head_y = slake->head_y;

	int x_diff = 0;
	int y_diff = 0;
	
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
	
	if (!in_rect(map, &slake->cells[0])) {
		slake->head_x = old_head_x;
		slake->head_y = old_head_y;

		y_diff = 0;
		x_diff = 0;

		if (mode == up || mode == down) {
			slake->mode = left;
		}
		else {
			slake->mode = down;
		}
		//TODO update clock
		return;
	}

	int head_delta_distance_x = abs((int) (round(old_head_x)-round(slake->head_x)));
	int head_delta_distance_y = abs((int) (round(old_head_y)-round(slake->head_y)));
		
	// move head
	//TODO ??? IN FIRST FOR LOOP ???
	slake->cells[0].x += x_diff;
	slake->cells[0].y += y_diff;
	
	for (int i = 0; i <= head_delta_distance_x + head_delta_distance_y; i++) {
		
		write_log("Tail position: \n");
		// move slake tail  		
		for (int i = (slake->length - 1); i > 0; i--) {
			write_log("	Cell %d:\n", i);
			slake->cells[i] = slake->cells[i-1];	//TODO: i oder i-1?
			write_log("		x: %d\n", slake->cells[i].x);
			write_log("		y: %d\n", slake->cells[i].y);
		}
		write_log("\n");
	}
	
	// update clock after move
	slake->lastmove_clock = clock();
}


struct slake_t *slake_init(struct slake_t *slake, double head_x, double head_y, 
	int length, enum slake_mode_t mode, double speed)
{
	
	// from arguments
	slake->head_x = head_x;
	slake->head_y = head_y;
	slake->length = length;
	slake->mode = mode;
	slake->speed = speed;
	
	// position
	slake->cells = malloc(sizeof(struct slake_position_t) * length);
	
	write_log("Generate slake: \n");
	struct slake_position_t temp_position;
	for (int i = 0; i < length; i++) {
		write_log("     Cell %d:\n", i);
		temp_position.x = (int) head_x;
		temp_position.y = (int) head_y - i; 
		slake->cells[i] = temp_position;
		write_log("             x: %d\n", slake->cells[i].x);
 		write_log("             y: %d\n", slake->cells[i].y);
	} 
	
	slake->lastmove_clock = clock();
	
	return slake;

}

