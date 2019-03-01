#include<stdio.h>
#include<curses.h>
#include<signal.h>
 
int main()
{
	initscr(); 
	move(LINES/2,COLS/2);
	addstr("Hello!");
	move(2,2);
	addstr("User:");
	move(3,2);
	addstr("Pass:");
	getch();
 
	endwin();

	return 0;
}

