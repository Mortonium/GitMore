#pragma once

#include <string>
#include <curses.h>
#include <vector>
#include <thread>
#include <mutex>
#include <atomic>
#include <queue>
#include <git2.h>

#include "Repository.hpp"

#include "Settings.hpp"
#include "CLI.hpp"

enum class GitMoreState {
	None,
	Closing,
	CommandInput
};

class GitMore {

public:
	GitMore();
	~GitMore();

	void run();
	void waitForThreadFinish();

	GitMoreState getState() const;

	void keyPress(int chr);



private:
	std::thread* itsThread = nullptr;
	std::atomic<GitMoreState> itsState{ GitMoreState::None };
	Repository* itsCurrentRepository = nullptr;
	Settings itsSettings;

	std::queue<int> itsInputQueue;
	std::mutex itsInputQueueMutex;

	CLI itsCLI;



	void setState(GitMoreState s);

	void main();
	void interpretKeyPress(int ch);

	void setCurrentRepo(std::string path);
	void closeCurrentRepo();

	void executeCommandString(std::string commandString);
	void interpretCommand(std::string commandString);

	void draw();

};