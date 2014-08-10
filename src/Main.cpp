//#include "Main.hpp"

#include <curses.h>
#include <exception>
#include <iostream>

#include "gitmore.hpp"

int main(int argc, char** argv) {
	
	initscr();
	cbreak(); // Disable line buffering, keep things like CTRL-Z
	// raw(); // Disable line buffering, disable things like CTRL-Z
	noecho(); // Stops user input from being echoed
	keypad(stdscr, TRUE); // Enables function keys like F1, F2 and the arrow keys
	curs_set(0);
	if (has_colors())
		start_color();
	timeout(1000);
	
	gitmore gm;
	gm.run();

	bool exit = false;
	while (!exit) {
		int ch = getch();
		if (ch >= 0)
			gm.keyPress(ch);
		exit = gm.getState() == gitmore_state::closing;
	}

	endwin();
	gm.waitForThreadFinish();
	return 0;

}