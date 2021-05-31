//
// CM4Industrial TEST code V1.0
// Created by andy sheng in Nov 2020
//

//需要手动的放到后面，自动的都放到前面。
#include <ncurses.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
typedef struct funciton_link_list       //定义功能结构体
{
	char index;                           /*功能的序号*/
	char name[50];                       /*功能的名字*/
	char shell_name[50];                 /*要调用脚本文件*/
	int result;	                         /*功能测试的结果*/
	int x_pos;							 /*功能名显示的位置*/
	int y_pos;                           /*功能名显示的位置*/
	
}FUNCITON_LINK_LIST;

int max_y,max_x;
FUNCITON_LINK_LIST fun[]={
//	{'1',"1-RTC","sudo bash rtc.sh ",0,0,0},            /*RTC测试*/
//	{'2',"2-uhost2.0","sudo bash uhost2.0.sh",0,0,0},   /*USB2.0测试*/
//	{'3',"3-SPI-flash"," sudo bash spi.sh",0,0,0},		/*SPI-flash测试*/	
//	{'4',"5-buzzer","sudo bash buzzer.sh",0,0,0},	    /*buzzer测试*/
//	{'5',"6-button","sudo bash button.sh",0,0,0},       /*button测试*/
//	{'6',"7-fan","sudo bash fan.sh",0,0,0},             /*fan测试*/
//	{'7',"8-4G","sudo bash 4G.sh ",0,0,0},              /*4G测试*/
//	{'8',"9-DI1","sudo bash DI1.sh ",0,0,0},            /*DI1测试*/
//	{'9',"a-DI2","sudo bash DI2.sh ",0,0,0},            /*DI2测试*/
	{'a',"c-camera","sudo bash camera.sh",0,0,0},      /*camera测试*/
	
	
	
	
//{'4',"4-RS232"," sudo bash RS232.sh",0,0,0},        /*RS232测试*/
//	{'a',"a-REALY-DO"," ",0,0,0},
//	{'b',"b-adc"," ",0,0,0},
//  {'c',"c-camera"," ",0,0,0},
//	{'d',"d-4G"," ",0,0,0},
//	{'e',"e-eth0"," ",0,0,0},
	//{'f',"f-eth1"," ",0,0,0}	
	//{'d',"d-RS485"," ",0,0,0}
    //最后要调换以下顺序	
};

//
/*初始化各个功能的显示坐标*/
//
int init_setpos_function(int max_y ,int max_x)  
{

	int x,y;                      				/*循环坐标的变量*/
	int fun_index=0;              				/*功能函数的下标*/
	
	int length = sizeof(fun)/sizeof(fun[0]);    /*获取功能函数的个数*/
	
	for(y=max_y/6;y<=max_y;y=y+(max_y/3))       /*因为显示的是三行格，需要在每一行的中间显示*/
	{
		for(x=max_x/16;x<=max_x;x=x+max_x/8)    
		{
			fun[fun_index].x_pos=x;
			fun[fun_index].y_pos=y;
            fun_index++;
			if(fun_index > length-1)              /*超过功能函数的个数，退出*/
			{
				break;
			}
		}
		if(fun_index > length-1)       			/*超过功能函数的个数，退出*/
			{
				break;
			}
	}
	refresh();
	return 0;
}
//
/*初始化测试框架*/
//
int frame_show(int max_y ,int max_x)
{
	int i;
	int x,y;
	initscr();     									//初始化虚拟屏幕
	
	for(y=max_y/3;y<=max_y;y=y+max_y/3)              //打印两条横线
	{
		for(i=0;i<max_x;i++)  
		{
		   mvprintw(y,i,"-");
		}
	}
	x=max_x/8;	   //
	for(;x<=max_x;x=x+max_x/8)
	{
	  for(y=0;y<max_y;y++)
	  {
		 mvprintw(y,x,"|");	
	  }
	}	
	mvprintw(0,max_x/2-10,"CM4Industrial TEST V1.0");
	refresh();
	return 0;
}
//
/*显示功能名称*/
//
int function_show(void)
{
	int x,y;
	int fun_index=0;
	int length = sizeof(fun)/sizeof(fun[0]);
	initscr();
	for(fun_index=0;fun_index<length;fun_index++)
	{
		mvprintw(fun[fun_index].y_pos,fun[fun_index].x_pos-3,fun[fun_index].name);
	}
	refresh();
	return 0;
}
int run_test()
{
	int fun_index=0;
	int ret_value;
	char key_value;
	WINDOW *my_win;
	int length = sizeof(fun)/sizeof(fun[0]);
	
	for(fun_index=0;fun_index<length;fun_index++)
	{
		ret_value = system(fun[fun_index].shell_name);
	    //sprintf(str, "ret_value = %d     ", ret_value);
	    initscr();
		if(ret_value == 0)      				 //结果为0表示shell调用成功并且功能测试成功。
		{
			if(fun[fun_index].index == 'a')  //摄像头调用脚本正常。
			{
				my_win = newwin(max_y/2,max_x/2,max_y/3,max_x/3);
				//box(my_win,0,0);
				mvwprintw(my_win,0,0,"Is the camrea working properly?");
				wrefresh(my_win);
				
		        key_value = getchar();
			}
			// wborder(my_win, ' ', ' ', ' ',' ',' ',' ',' ',' ');
			 wrefresh(my_win);			 
			 delwin(my_win);
			 
			if(key_value == 'o'||key_value == 'O')
			{
				init_pair(1,COLOR_GREEN,COLOR_BLACK);
				attron(COLOR_PAIR(1));
				mvprintw(fun[fun_index].y_pos+1,fun[fun_index].x_pos-3,"PASS");
				attroff(COLOR_PAIR(1));
			}
			else 
			{
				init_pair(2,COLOR_RED,COLOR_BLACK);
				attron(COLOR_PAIR(2));
				mvprintw(fun[fun_index].y_pos+1,fun[fun_index].x_pos-3,"FAIL");
				attroff(COLOR_PAIR(2));
			}	
		}
		else if (ret_value == 256) 				//结果为256表示shell调用成功但是功能测试失败。
		{
			init_pair(2,COLOR_RED,COLOR_BLACK);
			attron(COLOR_PAIR(2));
			mvprintw(fun[fun_index].y_pos+1,fun[fun_index].x_pos-3,"FAIL");
			attroff(COLOR_PAIR(2));
		}
		else  //其它值表示shell调用失败。
		{
			init_pair(2,COLOR_RED,COLOR_BLACK);
			attron(COLOR_PAIR(2));
			mvprintw(fun[fun_index].y_pos+1,fun[fun_index].x_pos-3,"ERROR");
			attroff(COLOR_PAIR(2)); 
		}	
		refresh();
	}
	return 0;
}
void retest(void)
{
	int fun_index=0;
	int ret_value;
	int length = sizeof(fun)/sizeof(fun[0]);
	while(1)
	{
		char key_value;
		key_value = getchar();
		for(fun_index=0;fun_index<length;fun_index++)
		{
			if(key_value == fun[fun_index].index)
			{
				
				//sprintf(str, "ret_value = %d     ", ret_value);
				initscr();
	
				init_pair(0,COLOR_BLACK,COLOR_BLACK);
				attron(COLOR_PAIR(0));
				mvprintw(fun[fun_index].y_pos+1,fun[fun_index].x_pos-3,"PASS");
				attroff(COLOR_PAIR(0));
				refresh();
				
				ret_value = system(fun[fun_index].shell_name);
				
				if(ret_value == 0)      				 //结果为0表示shell调用成功并且功能测试成功。
				{

					init_pair(1,COLOR_GREEN,COLOR_BLACK);
					attron(COLOR_PAIR(1));
					mvprintw(fun[fun_index].y_pos+1,fun[fun_index].x_pos-3,"PASS");
					attroff(COLOR_PAIR(1));
					
				}
				else if (ret_value == 256) 				//结果为256表示shell调用成功但是功能测试失败。
				{
					init_pair(2,COLOR_RED,COLOR_BLACK);
					attron(COLOR_PAIR(2));
					mvprintw(fun[fun_index].y_pos+1,fun[fun_index].x_pos-3,"FAIL");
					attroff(COLOR_PAIR(2));
				}
				else  									//其它值表示shell调用失败。
				{
					init_pair(2,COLOR_RED,COLOR_BLACK);
					attron(COLOR_PAIR(2));
					mvprintw(fun[fun_index].y_pos+1,fun[fun_index].x_pos-3,"ERROR");
					attroff(COLOR_PAIR(2)); 
				}	
				refresh();
				break;
			}
					
		}
		
	}
}

int main(int argc, char *argv[])
{
	WINDOW *local_win;
	//char str[80];
	initscr();
	start_color();
	getmaxyx(stdscr,max_y,max_x);
	frame_show(max_y,max_x);
	init_setpos_function(max_y,max_x);
	function_show();
    run_test();
	refresh();
	retest();
	
	
	endwin();
	return 0;
}




	
