#pragma once

#include <curses.h>
#include <string>
#include <vector>
#include <boost\spirit\include\qi.hpp>

#include "CLIToken.hpp"

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
	CLIToken itsCurrentCLIToken;
	std::vector<CLIToken> itsCLITokens;
	std::vector<std::string> itsNextValidTokens;

	void pushCurrentCLIToken();

	void validateAllTokens();

};