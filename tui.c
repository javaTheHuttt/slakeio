


void init_tui(void) {
	int tbe = tb_init();
	if (tbe < 0) {perror("tb error %d", tbe);exit(1);}
	tbw = tb_width();
	tbh = tb_height();
	
}

void draw(void) {
	//screen center shoudl be the position of the head of the slake
	struct slake_position screen_center = my_slake->cells[0];
	 

}
