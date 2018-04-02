#include <clock.h>
int main(int argc, char *argv []) {return 0;}

//move
void move(void)
{
	struct slake_position head = myslake->cells;
	enum slake_mode mode = slake->mode;
	//new array (new head + old cells-1)
		struct slake_position *newcells;
		if(mode == left) {*newcells = head->x--;}
		else if(mode == up) {*newcells = head->y++;}
		else if(mode == right) {*newcells = head->x++;}
		else {*newcells = head->y--;}
		for(int i = 1, i <(myslake->length), i++) {newcells[i] = cells[i-1];}
		free(cells);
		cells = newcells;
}

