#include "CLI.hpp"

CLI::CLI() { }
CLI::~CLI() {
	delwin(itsInputWindow);
}

void CLI::init() {
	itsCommand = "";
	clear();
	mvhline(getmaxy(stdscr) - 2, 0, '-', COLS);
	refresh();
	itsInputWindow = newwin(1, COLS, getmaxy(stdscr) - 1, 0);
	wmove(itsInputWindow, 0, 0);
}

void CLI::keyPress(chtype ch) {
	if (!itsFinished) {
		if ((ch >= 32) && (ch <= 126)) {
			itsCommand += (char)ch;
			//mvaddch(getmaxy(stdscr) - 1, itsCommand.length() - 1, (char)ch);
			waddch(itsInputWindow, (char)ch);
		} else if (ch == 8) { // Backspace
			if (itsCommand.length() > 0) {
				itsCommand.erase(itsCommand.end() - 1);
				mvwdelch(itsInputWindow, getmaxy(stdscr) - 1, itsCommand.length());
			}
		} else if (ch == 10) { // Enter
			itsFinished = true;
		}
		wrefresh(itsInputWindow);
	}
}
bool CLI::finished() {
	return itsFinished;
}
std::string CLI::getCommand() {
	return itsCommand;
}