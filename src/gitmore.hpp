#pragma once

#include <string>
#include <curses.h>
#include <vector>
#include <thread>
#include <mutex>
#include <atomic>
#include <queue>
#include <git2.h>

#include "git/repository.hpp"

#include "Settings.hpp"
#include "CLI.hpp"

enum class gitmore_state {
	none,
	closing,
	command_input
};

class gitmore {

public:
	gitmore();
	~gitmore();

	void run();
	void waitForThreadFinish();

	gitmore_state getState() const;

	void keyPress(int chr);



private:
	std::thread* itsThread = nullptr;
	std::atomic<gitmore_state> itsState{ gitmore_state::none };
	git::repository* itsCurrentRepository = nullptr;
	Settings itsSettings;

	std::queue<int> itsInputQueue;
	std::mutex itsInputQueueMutex;

	CLI itsCLI;



	void setState(gitmore_state s);

	void main();
	void interpretKeyPress(int ch);

	void setCurrentRepo(std::string path);
	void closeCurrentRepo();

	void executeCommandString(std::string commandString);
	void interpretCommand(std::string commandString);

	void draw();

};