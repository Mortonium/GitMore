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
		if ((ch >= 33) && (ch <= 126)) { // Character
			if (itsCurrentCommandToken.inUse()) {
				itsCurrentCommandToken.addCharacter((char)ch);
			} else {
				itsCurrentCommandToken = CLIToken((char)ch, itsCommand.length());
			}
			//mvaddch(getmaxy(stdscr) - 1, itsCommand.length() - 1, (char)ch);
			itsCommand += (char)ch;
			waddch(itsInputWindow, (char)ch);
		} else if (ch == 32) { // Space
			if (itsCurrentCommandToken.inUse()) {
				itsCommandTokens.push_back(itsCurrentCommandToken);
				itsCurrentCommandToken.clear();
			}
			itsCommand += (char)ch;
			waddch(itsInputWindow, (char)ch);
		} else if (ch == 8) { // Backspace
			if (itsCommand.length() > 0) {
				if (itsCurrentCommandToken.inUse()) {
					itsCurrentCommandToken.removeCharacter();
				} else {
					if ((itsCommand.length()) > 1 && (*(itsCommand.end() - 2) != ' ')) {
						itsCurrentCommandToken = itsCommandTokens.back();
						itsCommandTokens.pop_back();
					}
				}
				itsCommand.erase(itsCommand.end() - 1);
				mvwdelch(itsInputWindow, getmaxy(itsInputWindow) - 1, itsCommand.length());
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