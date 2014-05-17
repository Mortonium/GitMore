//#include "Main.hpp"

#include <curses.h>
#include <exception>
#include <iostream>

#include "GitMore.hpp"

int main(int argc, char** argv) {
	
	initscr();
	cbreak(); // Disable line buffering, keep things like CTRL-Z
	// raw(); // Disable line buffering, disable things like CTRL-Z
	noecho(); // Stops user input from being echoed
	keypad(stdscr, TRUE); // Enables function keys like F1, F2 and the arrow keys
	timeout(100);

	GitMore gitmore;
	gitmore.run();

	bool exit = false;
	while (!exit) {
		int ch = getch();
		gitmore.keyPress(ch);
		exit = gitmore.getState() == GitMoreState::Closing;
	}

	endwin();
	gitmore.waitForThreadFinish();
	return 0;

}