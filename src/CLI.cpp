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
			itsCurrentToken += (char)ch;
			//mvaddch(getmaxy(stdscr) - 1, itsCommand.length() - 1, (char)ch);
			itsCommand += (char)ch;
			waddch(itsInputWindow, (char)ch);
		} else if (ch == 32) { // Space
			if (itsCurrentToken.length() > 0) {
				itsCommandTokens.push_back(itsCurrentToken);
				itsCurrentToken = "";
			}
			itsCommand += (char)ch;
			waddch(itsInputWindow, (char)ch);
		} else if (ch == 8) { // Backspace
			if (itsCommand.length() > 0) {
				if (itsCurrentToken.length() > 0) {
					itsCurrentToken.erase(itsCurrentToken.end() - 1);
				} else {
					if ((itsCommand.length()) > 1 && (*(itsCommand.end() - 2) != ' ')) {
						itsCurrentToken = itsCommandTokens.back();
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

void CLI::tokenizeCommand() {

	std::string currentToken = "";
	for (std::string::const_iterator iter = itsCommand.begin(); iter != itsCommand.end(); iter++) {

	}
}
void CLI::checkTokenStatus() {

}