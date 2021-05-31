

//
// CM4Industrial TEST code V1.0
// Created by andy sheng in Nov 2020
//


#include <ncurses.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
int main(int argc, char *argv[])
{
	int max_y=22,max_x=22;
	initscr();
	start_color();
	init_pair(1,COLOR_RED,COLOR_BLACK);
	attron(COLOR_PAIR(1));
	mvprintw(max_y,max_x,"PASS");
	attroff(COLOR_PAIR(1));
	refresh();
	getchar();
	endwin();
	return 0;
}

