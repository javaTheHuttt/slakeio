#include <termbox.h>
#include <stdio.h>
#include <string.h>
#include <unistd.h>

enum gamestatus {
	startmenu,
	playing,
	pausemenu,
	win,
	lost};


struct tb_cell menu = {
	.ch = ' ',
	.fg = TB_DEFAULT,
	.bg = TB_BLACK
};

void put_menu_header(char *option, uint16_t style, int x, int y)
{
	int option_str_length = strlen(option);	
	for(int i = 0; i<option_str_length; i++)
	{
		tb_change_cell(x+i,y+2, '+', TB_BLUE, TB_BLACK);
		tb_change_cell(x+i,y,option[i] , style , TB_BLACK);
		tb_change_cell(x+i,y-2, '+', TB_BLUE, TB_BLACK);
	}
	//seiten
	for(int j = 0; j<5; j++)
	{
		tb_change_cell(x-1,y+2-j, '+', TB_BLUE, TB_BLACK);
		tb_change_cell(x+option_str_length, y+2-j, '+', TB_BLUE, TB_BLACK);
	}
}

void put_menu_option(char *option, uint16_t style, int x, int y)
{
	int option_str_length = strlen(option);	
	for(int i = 0; i<option_str_length; i++)
	{
		tb_change_cell(x+i,y,option[i] , style , TB_BLACK);
		tb_change_cell(x+i,y+1, '+', TB_BLUE, TB_BLACK);
	}
}


void put_background(int start_x, int start_y,int end_x,int end_y)
{
	for(int j = start_y; j<end_y; j++)
	{
		for(int i = start_x; i<end_x; i++)
		{
			tb_change_cell(i,j, ' ', TB_DEFAULT, TB_BLACK);
		}
	}
}


int main(void)
{
	tb_init();


	while(1) {

		//stuff to calculate the center & enter the strings
		int width = tb_width();
		int height = tb_height();	
		char *welcome = "  Willkommen in SlakeWorld!  ";
		char *start = " Start ";
		int welcome_lenght = strlen(welcome);
		int start_lenght = strlen(start);
		int welcome_height = height/2;
		int welcome_begin = width/2 -(welcome_lenght/2);
		int start_begin = (welcome_lenght/2) - (start_lenght/2);
		put_background(0,0,width,height);

		put_menu_header(welcome, TB_BLUE ,welcome_begin, welcome_height);
		put_menu_option(start, TB_BLUE, welcome_begin+start_begin,welcome_height+5
);

		tb_present();

		//Input
		struct tb_event input;
		char *letsgo = "LETS GO";
		


		tb_peek_event(&input, 100);
		switch(input.key){
			case TB_KEY_ESC:
				goto exit;
			case TB_KEY_ENTER:
				put_menu_option(start, TB_GREEN, welcome_begin+start_begin,welcome_height+5);
				tb_present();
				break;
			//	goto game;
			
			}
		
	
	}		
/*game:
			tb_peek_event(&begin, 100);
		int width = tb_width();
		int height = tb_height();	
		char *welcome = "Willkommen in SlakeWorld!";
		char *start = "Start";
		int welcome_lenght = strlen(welcome);
		int start_lenght = strlen(start);
		int welcome_height = height/2;
		int welcome_begin = width/2 -(welcome_lenght/2);
		int start_begin = (welcome_lenght/2) - (start_lenght/2);
	switch(begin.key){
				case TB_KEY_ESC:
					goto exit;
				case TB_KEY_ENTER:
					put_menu_option(start, TB_RED, welcome_begin+start_begin,welcome_height+5);
					tb_present();

				}
*/
exit:
	tb_shutdown();
return(0);
}
