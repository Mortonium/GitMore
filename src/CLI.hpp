#pragma once

#include <curses.h>
#include <string>
#include <vector>

enum class CommandTokenStatus {
	Valid,
	InvalidSyntax,
	InvalidValue
};

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
	std::string itsCurrentToken = "";
	std::vector<std::string> itsCommandTokens;
	std::vector<CommandTokenStatus> itsCommandTokenStatus;

	void tokenizeCommand();
	void checkTokenStatus();

};