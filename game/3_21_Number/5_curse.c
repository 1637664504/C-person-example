#include<unistd.h>
#include<curses.h>

int main()
{
	initscr();

	box(stdscr, ACS_VLINE, ACS_HLINE); /*draw a box*/
	move(LINES/2, COLS/2); /*move the cursor to the center*/
	waddstr(stdscr, "Hello, world!"); 
	move(2, 2);
	waddstr(stdscr, "==========");
	refresh();
	getch();

	endwin();
	return 0;
}

