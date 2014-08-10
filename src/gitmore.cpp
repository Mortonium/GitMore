#include "gitmore.hpp"

#include <iostream>

gitmore::gitmore() {
	
}
gitmore::~gitmore() {
	if (its_thread) {
		delete its_thread;
	}
}

void gitmore::run() {
	if (!its_thread) {
		its_thread = new std::thread(&gitmore::main, this);
	}
}
void gitmore::wait_for_thread_finish() {
	try {
		if (its_thread && its_thread->joinable()) its_thread->join();
	} catch (std::invalid_argument ex) {
		std::cerr << "Thread unjoinable, no biggy" << std::endl;
	} catch (std::exception ex) {
		std::cerr << "Unaccounted thread exception: \n" << ex.what() << std::endl;
	}
}

gitmore_state gitmore::get_state() const {
	return its_state;
}
void gitmore::key_press(int chr) {
	its_input_queue_mutex.lock();
	its_input_queue.push(chr);
	its_input_queue_mutex.unlock();
}





void gitmore::set_state(gitmore_state s) {
	its_state = s;
}

void gitmore::main() {

	git_threads_init();
	set_current_repo("E:/Repos/TestRepo/");
	
	while (its_state != gitmore_state::closing) {

		its_input_queue_mutex.lock();
		if (its_input_queue.empty())
			its_input_queue_mutex.unlock(); 
		else {

			std::queue<int> cached_input_queue = its_input_queue;
			while (!its_input_queue.empty()) its_input_queue.pop();
			its_input_queue_mutex.unlock();

			while (cached_input_queue.size() > 0) {
				int temp = cached_input_queue.front();
				interpret_key_press(cached_input_queue.front());
				cached_input_queue.pop();
			}

			if (its_state == gitmore_state::command_input) {
				if (its_CLI.finished()) {
					execute_command_string(its_CLI.getCommand());
				}
			}

		}

		std::this_thread::sleep_for(std::chrono::milliseconds(100));

	}
	
}
void gitmore::interpret_key_press(int ch) {
	if (ch == 27) {
		set_state(gitmore_state::closing);
	} else {
		if (its_state == gitmore_state::none) {
			if (ch == 9) { // TAB
				set_state(gitmore_state::command_input);
				its_CLI.init();
			}
		} else if (its_state == gitmore_state::command_input) {
			its_CLI.keyPress(ch);
		}
	}
}

void gitmore::set_current_repo(std::string path) {

	git::repository* new_repo = new git::repository(path);
	close_current_repo();
	its_current_repository = new_repo;

	draw();

}
void gitmore::close_current_repo() {
	if (its_current_repository) {
		delete its_current_repository;
		its_current_repository = nullptr;
	}
}

void gitmore::execute_command_string(std::string commandString) {
	mvprintw(0, 0, commandString.c_str());
	refresh();
}
void gitmore::interpret_command(std::string commandString) {
	
}

void gitmore::draw() {
	clear();

	std::string close_message = "Closing";

	switch (its_state) {

	case gitmore_state::none:
		if (its_current_repository) {
			mvprintw(0, 0, its_current_repository->get_path().c_str());
			//mvprintw(1, 0, "## %s\n", itsCurrentRepository->getCurrentBranchName()/.length() ? itsCurrentBranch.c_str() : "HEAD (no branch)");
		}
		break;
		
	case gitmore_state::closing:
		mvprintw(getmaxy(stdscr) / 2, (getmaxx(stdscr) / 2) - (close_message.length() / 2), close_message.c_str());
		break;

	case gitmore_state::command_input:
		for (int i = 0; i < getmaxx(stdscr); i++)
			mvaddch(getmaxy(stdscr) - 2, i, '=');
		//mvprintw(getmaxy(stdscr) - 1, 0, itsCommand.c_str());
		break;

	}

	refresh();
}