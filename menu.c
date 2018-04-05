#include <termbox.h>
#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <stdlib.h>
#include "slakeio.h"

//helperfunctions
void put_menu_header(char *header, uint16_t style, int x, int y)
{
	int header_str_length = strlen(header);	
	for(int i = 0; i<header_str_length; i++)
	{
		tb_change_cell(x+i,y+2, '+', TB_BLUE, TB_BLACK);
		tb_change_cell(x+i,y,header[i] , style , TB_BLACK);
		tb_change_cell(x+i,y-2, '+', TB_BLUE, TB_BLACK);
	}
	//seiten
	for(int j = 0; j<5; j++)
	{
		tb_change_cell(x-1,y+2-j, '+', TB_BLUE, TB_BLACK);
		tb_change_cell(x+header_str_length, y+2-j, '+', TB_BLUE, TB_BLACK);
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


//****STARTMENU****
void startmenu(void)
{
	//stuff to calculate the center & enter the strings
	int width = tb_width();
	int height = tb_height();	
	char *welcome = "  Willkommen in SlakeWorld!  ";
	char *start = " press ENTER to play ";

	int welcome_lenght = strlen(welcome);
	int start_lenght = strlen(start);
	int welcome_height = height/2;
	int welcome_begin = width/2 -(welcome_lenght/2);
	int start_begin = (welcome_lenght/2) - (start_lenght/2);

	put_background(0,0,width,height);
	put_menu_header(welcome, TB_BLUE ,welcome_begin, welcome_height);
	put_menu_option(start, TB_BLUE, welcome_begin+start_begin,welcome_height+8
);
	tb_present();
	while(1) {
		//Input
		struct tb_event input;

		tb_peek_event(&input, 100);
		switch(input.key){
			case TB_KEY_ESC:
				loop=0;
				return;
			case TB_KEY_ENTER:
				put_menu_option(start, TB_GREEN, welcome_begin+start_begin,welcome_height+8);
				tb_present();
				while(1)
				{
					struct tb_event waiting_start;
					tb_peek_event(&waiting_start, 100);
					switch(waiting_start.key){
						case TB_KEY_ESC:
							loop=0;
							return;
						case TB_KEY_ENTER:
							status = playing_status;
							return;
					}
				}
			}
	}		
}

//****WIN****
void win(void) 
{
	char *win = " YOU WON ";
	char *score = malloc(80 * sizeof(char));
	sprintf(score, "Your score: %d", my_slake->length);
	char *instruction2 = " press Enter to play ";
	char *instruction3 = " press ESC to exit ";

	int width = tb_width();
	int height = tb_height();	
	int win_lenght = strlen(win);
	int score_lenght = strlen(score);
	int win_height = height/2;
	int win_begin = width/2 -(win_lenght/2);
	int score_begin = (score_lenght/2) - (win_lenght/2);
	
	put_background(0,0,width,height);
	put_menu_header(win, TB_GREEN,win_begin, win_height);
	put_menu_option(score, TB_GREEN, score_begin, win_height+8);
	put_menu_option(instruction2, TB_BLUE,win_begin, win_height+11);
	put_menu_option(instruction3, TB_BLUE,win_begin, win_height+13);
	tb_present();	
	while(1)
	{
		struct tb_event input;
		tb_peek_event(&input, 100);
		switch(input.key) {
			case TB_KEY_ESC:
				loop=0;
				return;
			case TB_KEY_ENTER:
				game_uninit();
				game_init();
				status = playing_status;
				return;
		}
	}
}

//****LOST****
void lost(void)
{
	char *lost = " YOU LOST ";
	char *score = malloc(80 * sizeof(char));
	sprintf(score, "Your score: %d", my_slake->length);
	char *instruction2 = " press Enter to play ";
	char *instruction3 = " press ESC to exit ";

	int width = tb_width();
	int height = tb_height();	
	int lost_lenght = strlen(lost);
	int score_lenght = strlen(score);
	int lost_height = height/2;
	int lost_begin = width/2 -(lost_lenght/2);
	int score_begin = (score_lenght/2) - (lost_lenght/2);
	
	put_background(0,0,width,height);
	put_menu_option(lost, TB_RED, lost_begin, lost_height);
	put_menu_option(score, TB_GREEN, score_begin, lost_height+8);
	put_menu_option(instruction2, TB_BLUE,lost_begin, lost_height+11);
	put_menu_option(instruction3, TB_BLUE,lost_begin, lost_height+13);	
	tb_present();	

	while(1)
	{
		struct tb_event input;
		tb_peek_event(&input, 100);
		switch(input.key) {
			case TB_KEY_ESC:
				loop=0;
				return;
			case TB_KEY_ENTER:
				game_uninit();
				game_init();
				status = playing_status;
				return;	
		}
	}
}

