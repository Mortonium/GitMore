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
	switch (chr) {
	case 27: // ESC
		itsState = GitMoreState::Closing;
		break;
	default:
		itsInputQueueMutex.lock();
		itsInputQueue.push(chr);
		itsInputQueueMutex.unlock();
		break;
	}
}





void GitMore::main() {

	git_threads_init();
	setCurrentRepo("E:\\Repos\\TestRepo\\");
	
	while (itsState != GitMoreState::Closing) {

		itsInputQueueMutex.lock();
		if (itsInputQueue.empty())
			itsInputQueueMutex.unlock(); 
		else {
			std::queue<int> cachedInputQueue = itsInputQueue;
			itsInputQueueMutex.unlock();

		}

		std::this_thread::sleep_for(std::chrono::milliseconds(100));

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

void GitMore::interpretCommand(std::string commandString) {
	
}

void GitMore::draw() {
	clear();

	if (itsCurrentRepository) {
		mvprintw(0, 0, itsCurrentRepository->getPath().c_str());
		//mvprintw(1, 0, "## %s\n", itsCurrentRepository->getCurrentBranchName()/.length() ? itsCurrentBranch.c_str() : "HEAD (no branch)");
	}

	refresh();
}