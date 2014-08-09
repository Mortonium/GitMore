#pragma once

#include <string>
#include <curses.h>

enum class CommandTokenStatus {
	None,
	Valid,
	InvalidSyntax,
	InvalidValue
};



class CLIToken {

public:
	CLIToken();
	CLIToken(char token, int startIndex);
	CLIToken(std::string token, int startIndex);
	void clear();
	bool inUse();

	void setToken(std::string token);
	void addCharacter(char ch);
	void removeCharacter();
	void setStatus(CommandTokenStatus status);

	std::string getToken();
	CommandTokenStatus getStatus();
	int getStartIndex();
	int getEndIndex();

	void drawToken(WINDOW* window, int row, int col);

private:
	std::string itsToken = "";
	CommandTokenStatus itsStatus =  CommandTokenStatus::None;
	int itsStartIndex = -1; // Inclusive
	int itsEndIndex = -1; // Inclusive

};