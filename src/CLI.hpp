#pragma once

#include <curses.h>
#include <string>
#include <vector>

class CLI {

public:
	CLI();

	void init();

	void keyPress(chtype ch);
	bool finished();
	std::string getCommand();

private:
	WINDOW* itsWindow = nullptr;
	bool itsFinished = false;

	std::string itsCommand = "";
	std::vector<std::string> itsCommandTokens;

};