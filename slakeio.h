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
	//lastmove_time
	double lastmove_clock;
	//speed (in Zeichen pro Sekunde)
	double speed; 
	//functions

	// creates slake with given parameters
	struct slake *init(position spawn, int length, enum slake_mode mode);
	// removes last cell of cells array and adds the first according to mode
	// changes are made relative to system time
	void move(struct slake slake_player);	
	
};

static const struct tb_cell empty;
static const struct tb_cell myslake_player;
static const struct tb_cell enemy_player;



struct slake_position {
	double x;
	double y;
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


