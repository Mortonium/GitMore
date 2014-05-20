#include "CLIToken.hpp"

#include <assert.h>

CLIToken::CLIToken() { }
CLIToken::CLIToken(char token, int startIndex) {
	itsStartIndex = startIndex;
	setToken(std::string(1, token));
}
CLIToken::CLIToken(std::string token, int startIndex) {
	itsStartIndex = startIndex;
	setToken(token);
}
void CLIToken::clear() {
	itsToken = "";
	itsStatus = CommandTokenStatus::None;
	itsStartIndex = -1;
	itsEndIndex = -1;
}
bool CLIToken::inUse() {
	return itsStartIndex >= 0;
}

void CLIToken::setToken(std::string token) {
	assert(inUse());
	if (token.length() == 0) {
		clear();
	} else {
		itsToken = token;
		itsEndIndex = itsStartIndex + token.length() - 1;
	}
}
void CLIToken::addCharacter(char ch) {
	assert(inUse());
	itsToken += ch;
	itsEndIndex++;
}
void CLIToken::removeCharacter() {
	assert(inUse());
	itsToken.erase(itsToken.end() - 1);
	itsEndIndex--;
	if (itsToken.length() == 0)
		clear();
}
void CLIToken::setStatus(CommandTokenStatus status) {
	assert(inUse());
	itsStatus = status;
}

std::string CLIToken::getToken() {
	assert(inUse());
	return itsToken;
}
CommandTokenStatus CLIToken::getStatus() {
	assert(inUse());
	return itsStatus;
}
int CLIToken::getStartIndex() {
	assert(inUse());
	return itsStartIndex;
}
int CLIToken::getEndIndex() {
	assert(inUse());
	return itsEndIndex;
}

void CLIToken::drawToken(WINDOW* window, int row, int col) {
	assert(inUse());
	init_pair(1, COLOR_RED, COLOR_BLACK);
	wattron(window, COLOR_PAIR(1));
	mvwprintw(window, row, col, itsToken.c_str());
	wrefresh(window);
	wattroff(window, COLOR_PAIR(1));
}