#include <termbox.h>
//
// LOGIC DECLARATIONS
//

enum slake_mode_t {left, up, right, down};

struct slake_t {
	//data
	struct slake_position_t *cells;
	//direction of movement
	enum slake_mode_t mode;
	// score or length of slake
	int length;

	//lastmove_time
	double lastmove_clock;
	//speed (in Zeichen pro Sekunde)
	double speed; 
	
	// head position 
	double head_x;
	double head_y;
	
};

struct slake_position_t {
	int x;
	int y;
};

// slake functions


// creates slake with given parameters
struct slake_t *slake_init(
	struct slake_t *slake,
	double head_x, 
	double head_y, 
	int length, 
	enum slake_mode_t mode,
	double speed
);
// removes last cell of cells array and adds the first according to mode
// changes are made relative to system time
void slake_move(struct slake_t *slake);

void game_init(void);


// global array that holds all slakes
struct slake_array_t {
	struct slake_t *array;
	int length;
};


struct slake_array_t *all_slakes;


//defines a square of cells (used for map size and screen)
struct slake_map_t {
	struct slake_position_t *upper_left;
	struct slake_position_t *bottom_right;
};


// defines the size of the map
struct slake_map_t map;


// 
double start_clock;
double slake_clock(void);


// pointer to the slake the user is controlling
struct slake_t *my_slake;
//
// TUI DECLARATIONS
//

//terminal width & height
int tbw;
int tbh;

void draw(void);

//
// CONTROL DECLARATIONS
//
//checks and changes mode (direction of slake)
void key_control(uint16_t key);
// a fuction that checks weather a position is inside a givin rect 
// returns true if it's inside
int in_rect(struct slake_map_t *rect, struct slake_position_t *pos);

