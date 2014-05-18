#pragma once

#include <curses.h>
#include <string>
#include <vector>

class CLI {

public:
	CLI();
	~CLI();

	void init();

	void keyPress(chtype ch);
	bool finished();
	std::string getCommand();

private:
	WINDOW* itsInputWindow = nullptr;
	bool itsFinished = false;

	std::string itsCommand = "";
	std::vector<std::string> itsCommandTokens;

};