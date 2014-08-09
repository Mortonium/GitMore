#include "CLI.hpp"

#include <algorithm>

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
			if (itsCurrentCLIToken.inUse()) {
				itsCurrentCLIToken.addCharacter((char)ch);
			} else {
				itsCurrentCLIToken = CLIToken((char)ch, itsCommand.length());
			}
			//mvaddch(getmaxy(stdscr) - 1, itsCommand.length() - 1, (char)ch);
			itsCommand += (char)ch;
			waddch(itsInputWindow, (char)ch);
		} else if (ch == 32) { // Space
			if (itsCurrentCLIToken.inUse()) {
				// itsCLITokens.push_back(itsCurrentCLIToken);
				// itsCurrentCLIToken.clear();
				pushCurrentCLIToken();
			}
			itsCommand += (char)ch;
			waddch(itsInputWindow, (char)ch);
		} else if (ch == 8) { // Backspace
			if (itsCommand.length() > 0) {
				if (itsCurrentCLIToken.inUse()) {
					itsCurrentCLIToken.removeCharacter();
				} else {
					if ((itsCommand.length()) > 1 && (*(itsCommand.end() - 2) != ' ')) {
						itsCurrentCLIToken = itsCLITokens.back();
						itsCLITokens.pop_back();
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





void CLI::pushCurrentCLIToken() {

	itsCLITokens.push_back(itsCurrentCLIToken);
	itsCurrentCLIToken.clear();

	if (std::find(itsNextValidTokens.begin(), itsNextValidTokens.end(), itsCLITokens.back().getToken()) == itsNextValidTokens.end()) { // Not valid
		itsCLITokens.back().setStatus(CommandTokenStatus::InvalidSyntax);
		itsCLITokens.back().drawToken(itsInputWindow, 0, itsCLITokens.back().getStartIndex());
	} else {
		itsCLITokens.back().setStatus(CommandTokenStatus::Valid);
		itsCLITokens.back().drawToken(itsInputWindow, 0, itsCLITokens.back().getStartIndex());
	}

	validateAllTokens();
	wmove(itsInputWindow, 0, itsCommand.length());

}

void CLI::validateAllTokens() {

	using namespace boost::spirit;
	
	std::string::iterator first = itsCommand.begin();
	std::string::iterator last = itsCommand.end();

	bool r = qi::phrase_parse(
		first,
		last,
		double_ >> *(',' >> double_),
		qi::space
		);
	mvhline(4, 0, ' ', 40);
	mvprintw(4, 0, "%s", std::string(itsCommand.begin(), first));
	refresh();
	//if (first != last) // fail if we did not get a full match
		//return false;

}