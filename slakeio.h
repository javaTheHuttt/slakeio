//
// LOGIC DECLARATIONS
//

enum slake_mode_t {left, up, right, down};

struct slake_t {
	//data
	struct slake_position *cells;
	//direction of movement
	enum slake_mode_t mode;
	// score or length of slake
	int length;
	

	
	
};
// slake functions

// creates slake with given parameters
struct slake_t *init(struct slake_position_t spawn, int length, enum slake_mode_t mode);
// removes last cell of cells array and adds the first according to mode
// changes are made relative to system time
void slake_move(struct slake_t *slake);


struct slake_position_t {
	int x;
	int y;
};


// global array that holds all slakes
struct slake_array_t {
	struct slake *array;
	int legth;
};


struct slake_array_t all_slakes;


//defines the size of the map
struct slake_map_t {
	struct slake_position_t upper_left;
	struct slake_position_t bottom_right;
};


// 
double start_clock;

double slake_clock(void);


// pointer to the slake the user is controlling
struct slake_t *my_slake;
//
// TUI DECLARATIONS
//

void draw(void);

// width of the terminal
int tbw;

// height of the terminal
int tbh;

