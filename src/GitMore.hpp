#pragma once

#include <string>
#include <curses.h>
#include <vector>
#include <thread>
#include <mutex>
#include <atomic>
#include <queue>
#include <git2.h>

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
	std::atomic<GitMoreState> itsState { GitMoreState::None };

	std::queue<int> itsInputQueue;
	std::mutex itsInputQueueMutex;

	std::string itsCurrentRepoPath;
	git_repository* itsCurrentRepo = nullptr;

	std::vector<std::string> itsCommandTokens;

	void main();

	void setCurrentRepo(std::string path);
	void closeCurrentRepo();

	void interpretCommand(std::string commandString);

	void draw();
	
};