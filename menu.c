#include <termbox.h>
#include <stdio.h>
#include <string.h>
#include <unistd.h>

struct tb_cell menu = {
	.ch = ' ',
	.fg = TB_DEFAULT,
	.bg = TB_BLACK
};

void put_menu_option(char *option, uint16_t style, int x, int y)
{
	int option_str_length = strlen(option);	
	for(int i = 0; i<option_str_length; i++)
	{
		tb_change_cell(x+i,y+1, '+', TB_BLUE, TB_WHITE);
		tb_change_cell(x+i,y,option[i] , style , TB_BLUE);
		tb_change_cell(x+i,y-1, '+', TB_BLUE, TB_WHITE);
	}
	//seiten
	for(int j = 0; j<3; j++)
	{
		tb_change_cell(x-1,y+1-j, '+', TB_BLUE, TB_WHITE);
		tb_change_cell(x+option_str_length, y+1-j, '+', TB_BLUE, TB_WHITE);
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
		put_background(0,0,width,height);
		char *welcome = "Willkommen in SlakeWorld!";
		char *start = "Start";
		int welcome_lenght = strlen(welcome);
		int start_lenght = strlen(start);
		int welcome_height = height/2;
		int welcome_begin = width/2 -(welcome_lenght/2);
		int start_begin = (welcome_lenght/2) - (start_lenght/2);
		put_menu_option(welcome, TB_BLACK ,welcome_begin, welcome_height);
		put_menu_option(start, TB_BLACK, welcome_begin+start_begin,welcome_height+5
);

		tb_present();

		//Input
		struct tb_event input;
		tb_peek_event(&input, 100);
		
		if(input.key == TB_KEY_ESC)
		{
			goto exit;}
		if(input.key == TB_KEY_ENTER)
		{
			put_menu_option(start, TB_GREEN, welcome_begin+start_begin,welcome_height+5);}
			
		}
		
	
exit:
	tb_shutdown();
return(0);
}
