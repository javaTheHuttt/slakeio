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
	//functions
	
};

struct slake_position_t {
	double x;
	double y;
};

// slake functions


// creates slake with given parameters
struct slake_t *init(struct slake_position_t spawn, int length, enum slake_mode_t mode);
// removes last cell of cells array and adds the first according to mode
// changes are made relative to system time
void slake_move(struct slake_t *slake);

static const struct tb_cell empty;
static const struct tb_cell myslake_player;
static const struct tb_cell enemy_player;







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

//terminal width & height
int tbw;
int tbh;

void draw(void);
//
// CONTROL DECLARATIONS
//

// log function to write something to the log.
void log(char *str);


