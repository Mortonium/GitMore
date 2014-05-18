#include "CLI.hpp"

CLI::CLI() { }

void CLI::init() {
	itsCommand = "";
	clear();
	move(getmaxy(stdscr) - 2, 0);
	for (int i = 0; i < getmaxx(stdscr); i++) {
		//mvaddch(getmaxy(stdscr) - 2, i, '=');
		addch('=');
	}
	move(getmaxy(stdscr) - 1, 0);
	refresh();
}

void CLI::keyPress(chtype ch) {
	if (!itsFinished) {
		if ((ch >= 32) && (ch <= 126)) {
			itsCommand += (char)ch;
			//mvaddch(getmaxy(stdscr) - 1, itsCommand.length() - 1, (char)ch);
			addch((char)ch);
		} else if (ch == 8) { // Backspace
			if (itsCommand.length() > 0) {
				itsCommand.erase(itsCommand.end() - 1);
				mvdelch(getmaxy(stdscr) - 1, itsCommand.length());
			}
		} else if (ch == 10) { // Enter
			itsFinished = true;
		}
		refresh();
	}
}
bool CLI::finished() {
	return itsFinished;
}
std::string CLI::getCommand() {
	return itsCommand;
}