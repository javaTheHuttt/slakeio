//
// LOGIC DECLARATIONS
//

enum slake_mode {left, up, right, down};

struct slake {
	//data
	struct slake_position *cells;
	//direction of movement
	enum slake_mode mode;
	// score or length of slake
	int length;
	
	//functions

	// creates slake with given parameters
	struct slake *init(position spawn, int length, enum slake_mode mode);
	// removes last cell of cells array and adds the first according to mode
	// changes are made relative to system time
	void move(void);	
	
};


struct slake_position {
	int x;
	int y;
};


// global array that holds all slakes
struct slake_array {
	struct slake *array;
	int legth;
};


struct slake_array all_slakes;


//defines the size of the map
struct slake_map {
	struct slake_position upper_left;
	struct slake_position bottom_right;
};


// 
double start_clock;

double slake_clock(void);


// pointer to the slake the user is controlling
struct slake *my_slake;
//
// TUI DECLARATIONS
//

void draw(void);

// width of the terminal
int tbw;

// height of the terminal
int tbh;

