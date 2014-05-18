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
	
	git_repository* newRepo = nullptr;
	int error = git_repository_open(&newRepo, path.c_str());
	if (error) {
		exit(error);
	} else {
		closeCurrentRepo();
		itsCurrentRepo = newRepo;
		itsCurrentRepoPath = path;
		
		/*
		git_status_list* statusList = nullptr;
		git_status_options o = GIT_STATUS_OPTIONS_INIT;
		o.show = GIT_STATUS_SHOW_INDEX_AND_WORKDIR;
		o.flags = GIT_STATUS_OPT_INCLUDE_UNTRACKED |
			GIT_STATUS_OPT_RENAMES_HEAD_TO_INDEX |
			GIT_STATUS_OPT_SORT_CASE_SENSITIVELY;
		git_status_list_new(&statusList, itsCurrentRepo, 0);
		*/

		int error = 0;
		git_reference *head = NULL;

		error = git_repository_head(&head, itsCurrentRepo);

		if (error == GIT_EUNBORNBRANCH || error == GIT_ENOTFOUND)
			itsCurrentBranch = "";
		else if (!error) {
			itsCurrentBranch = std::string(git_reference_shorthand(head));
		}

		git_reference_free(head);
		
		draw();

	}
	
}
void GitMore::closeCurrentRepo() {
	if (itsCurrentRepo) {
		git_repository_free(itsCurrentRepo);
		itsCurrentRepoPath = "";
		itsCurrentRepo = nullptr;
	}
}

void GitMore::interpretCommand(std::string commandString) {
	
}

void GitMore::draw() {
	clear();

	if (itsCurrentRepo) {
		mvprintw(0, 0, itsCurrentRepoPath.c_str());
		mvprintw(1, 0, "## %s\n", itsCurrentBranch.length() ? itsCurrentBranch.c_str() : "HEAD (no branch)");
	}

	refresh();
}