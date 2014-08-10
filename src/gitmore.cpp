#include "gitmore.hpp"

#include <iostream>

gitmore::gitmore() {
	
}
gitmore::~gitmore() {
	if (itsThread) {
		delete itsThread;
	}
}

void gitmore::run() {
	if (!itsThread) {
		itsThread = new std::thread(&gitmore::main, this);
	}
}
void gitmore::waitForThreadFinish() {
	try {
		if (itsThread && itsThread->joinable()) itsThread->join();
	} catch (std::invalid_argument ex) {
		std::cerr << "Thread unjoinable, no biggy" << std::endl;
	} catch (std::exception ex) {
		std::cerr << "Unaccounted thread exception: \n" << ex.what() << std::endl;
	}
}

gitmore_state gitmore::getState() const {
	return itsState;
}
void gitmore::keyPress(int chr) {
	itsInputQueueMutex.lock();
	itsInputQueue.push(chr);
	itsInputQueueMutex.unlock();
}





void gitmore::setState(gitmore_state s) {
	itsState = s;
}

void gitmore::main() {

	git_threads_init();
	setCurrentRepo("E:/Repos/TestRepo/");
	
	while (itsState != gitmore_state::closing) {

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

			if (itsState == gitmore_state::command_input) {
				if (itsCLI.finished()) {
					executeCommandString(itsCLI.getCommand());
				}
			}

		}

		std::this_thread::sleep_for(std::chrono::milliseconds(100));

	}
	
}
void gitmore::interpretKeyPress(int ch) {
	if (ch == 27) {
		setState(gitmore_state::closing);
	} else {
		if (itsState == gitmore_state::none) {
			if (ch == 9) { // TAB
				setState(gitmore_state::command_input);
				itsCLI.init();
			}
		} else if (itsState == gitmore_state::command_input) {
			itsCLI.keyPress(ch);
		}
	}
}

void gitmore::setCurrentRepo(std::string path) {

	git::repository* newRepo = new git::repository(path);
	closeCurrentRepo();
	itsCurrentRepository = newRepo;

	draw();

}
void gitmore::closeCurrentRepo() {
	if (itsCurrentRepository) {
		delete itsCurrentRepository;
		itsCurrentRepository = nullptr;
	}
}

void gitmore::executeCommandString(std::string commandString) {
	mvprintw(0, 0, commandString.c_str());
	refresh();
}
void gitmore::interpretCommand(std::string commandString) {
	
}

void gitmore::draw() {
	clear();

	std::string closeMessage = "Closing";

	switch (itsState) {

	case gitmore_state::none:
		if (itsCurrentRepository) {
			mvprintw(0, 0, itsCurrentRepository->get_path().c_str());
			//mvprintw(1, 0, "## %s\n", itsCurrentRepository->getCurrentBranchName()/.length() ? itsCurrentBranch.c_str() : "HEAD (no branch)");
		}
		break;
		
	case gitmore_state::closing:
		mvprintw(getmaxy(stdscr) / 2, (getmaxx(stdscr) / 2) - (closeMessage.length() / 2), closeMessage.c_str());
		break;

	case gitmore_state::command_input:
		for (int i = 0; i < getmaxx(stdscr); i++)
			mvaddch(getmaxy(stdscr) - 2, i, '=');
		//mvprintw(getmaxy(stdscr) - 1, 0, itsCommand.c_str());
		break;

	}

	refresh();
}