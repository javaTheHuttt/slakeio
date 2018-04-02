#include <clock.h>
int main(int argc, char *argv []) {
return 0;
}

//move
void move(struct slake)
{
	struct slake_position head = slake->cells;
	enum slake_mode mode = slake->mode;
	double delta_distance = speed*lastmove_clock;
	//new array (new head + old cells-1)
		struct slake_position *newcells;
		if(mode == left) {*newcells = head->x-delta_distance;}
		else if(mode == up) {*newcells = head->y+delta_distance;}
		else if(mode == right) {*newcells = head->x+delta_distance;}
		else {*newcells = head->y-delta_distance;}
		for(int i = 1, i <(myslake->length), i++) {newcells[i] = cells[i-1];}
		free(cells);
		cells = newcells;
		slake->lastmove_clock = clock();
}

