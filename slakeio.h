#include <termbox.h>
#include <stdio.h>

//
// LOGIC DECLARATIONS
//

//map const
#define MAP_SIZE_X  1000
#define MAP_SIZE_Y  1000


enum slake_mode_t {left, up, right, down};

struct slake_t {
	//data
	struct slake_position_t *cells;
	//direction of movement
	enum slake_mode_t mode;
	// score or length of slake
	int length;
	int old_length;

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

//food
//
//-functions
//--- init random food-coordinates and puts them in array food
void init_food(void);
//---checks if slake ate food
int check_food(struct slake_t *slake);
//---replaces used food-koordination with new one
void replace_food(int index_used_food);
//-food array
struct slake_position_t *food;

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
struct slake_map_t *map;


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

void init_tui(void);
//
// CONTROL DECLARATIONS
//
//checks and changes mode (direction of slake)
void key_control(uint16_t key);
// log function to write something to the log.
void slakeio_log(char *str);
// a fuction that checks weather a position is inside a givin rect 
// returns true if it's inside
int in_rect(struct slake_map_t *rect, struct slake_position_t *pos);


// logs
void init_log(void);				// inits log file
void write_log(const char *format, ...);	// formated log
void end_log(int print); // closes log file, print log after close 


