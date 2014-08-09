#include "GitMore.hpp"

#include <iostream>

GitMore::GitMore() {
	
}
GitMore::~GitMore() {
	if (itsThread) {
		delete itsThread;
	}
}

void GitMore::run() {
	if (!itsThread) {
		itsThread = new std::thread(&GitMore::main, this);
	}
}
void GitMore::waitForThreadFinish() {
	try {
		if (itsThread && itsThread->joinable()) itsThread->join();
	} catch (std::invalid_argument ex) {
		std::cerr << "Thread unjoinable, no biggy" << std::endl;
	} catch (std::exception ex) {
		std::cerr << "Unaccounted thread exception: \n" << ex.what() << std::endl;
	}
}

GitMoreState GitMore::getState() const {
	return itsState;
}
void GitMore::keyPress(int chr) {
	itsInputQueueMutex.lock();
	itsInputQueue.push(chr);
	itsInputQueueMutex.unlock();
}





void GitMore::setState(GitMoreState s) {
	itsState = s;
}

void GitMore::main() {

	git_threads_init();
	setCurrentRepo("E:/Repos/TestRepo/");
	
	while (itsState != GitMoreState::Closing) {

		itsInputQueueMutex.lock();
		if (itsInputQueue.empty())
			itsInputQueueMutex.unlock(); 
		else {

			std::queue<int> cachedInputQueue = itsInputQueue;
			while (!itsInputQueue.empty()) itsInputQueue.pop();
			itsInputQueueMutex.unlock();

			while (cachedInputQueue.size() > 0) {
				int temp = cachedInputQueue.front();
				interpretKeyPress(cachedInputQueue.front());
				cachedInputQueue.pop();
			}

			if (itsState == GitMoreState::CommandInput) {
				if (itsCLI.finished()) {
					executeCommandString(itsCLI.getCommand());
				}
			}

		}

		std::this_thread::sleep_for(std::chrono::milliseconds(100));

	}
	
}
void GitMore::interpretKeyPress(int ch) {
	if (ch == 27) {
		setState(GitMoreState::Closing);
	} else {
		if (itsState == GitMoreState::None) {
			if (ch == 9) { // TAB
				setState(GitMoreState::CommandInput);
				itsCLI.init();
			}
		} else if (itsState == GitMoreState::CommandInput) {
			itsCLI.keyPress(ch);
		}
	}
}

void GitMore::setCurrentRepo(std::string path) {

	Repository* newRepo = new Repository(path);
	closeCurrentRepo();
	itsCurrentRepository = newRepo;

	draw();

}
void GitMore::closeCurrentRepo() {
	if (itsCurrentRepository) {
		delete itsCurrentRepository;
		itsCurrentRepository = nullptr;
	}
}

void GitMore::executeCommandString(std::string commandString) {
	mvprintw(0, 0, commandString.c_str());
	refresh();
}
void GitMore::interpretCommand(std::string commandString) {
	
}

void GitMore::draw() {
	clear();

	std::string closeMessage = "Closing";

	switch (itsState) {

	case GitMoreState::None:
		if (itsCurrentRepository) {
			mvprintw(0, 0, itsCurrentRepository->getPath().c_str());
			//mvprintw(1, 0, "## %s\n", itsCurrentRepository->getCurrentBranchName()/.length() ? itsCurrentBranch.c_str() : "HEAD (no branch)");
		}
		break;
		
	case GitMoreState::Closing:
		mvprintw(getmaxy(stdscr) / 2, (getmaxx(stdscr) / 2) - (closeMessage.length() / 2), closeMessage.c_str());
		break;

	case GitMoreState::CommandInput:
		for (int i = 0; i < getmaxx(stdscr); i++)
			mvaddch(getmaxy(stdscr) - 2, i, '=');
		//mvprintw(getmaxy(stdscr) - 1, 0, itsCommand.c_str());
		break;

	}

	refresh();
}