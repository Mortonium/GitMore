#include "gitmore.hpp"

#include <iostream>

#include "git/branch.hpp"

gitmore::gitmore() {

}
gitmore::~gitmore() {
	if (its_thread)
		delete its_thread;
	if (its_header_window)
		delwin(its_header_window);

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
	its_header_window = newwin(2, COLS, 0, 0);
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
	wclear(its_header_window);

	draw_header();

	std::string close_message = "Closing";

	switch (its_state) {

	case gitmore_state::none:
		if (its_current_repository) {
			//mvprintw(0, 0, its_current_repository->get_path().c_str());
			//mvprintw(1, 0, "## %s\n", itsCurrentRepository->getCurrentBranchName()/.length() ? itsCurrentBranch.c_str() : "HEAD (no branch)");
		}
		break;
		
	case gitmore_state::closing:
		mvprintw(getmaxy(stdscr) / 2, (getmaxx(stdscr) / 2) - (close_message.length() / 2), close_message.c_str());
		break;

	case gitmore_state::command_input:
		//for (int i = 0; i < getmaxx(stdscr); i++)
			//mvaddch(getmaxy(stdscr) - 2, i, '=');
		//mvprintw(getmaxy(stdscr) - 1, 0, itsCommand.c_str());
		break;

	}

	refresh();
	wrefresh(its_header_window);

}

void gitmore::draw_header() {
	draw_header_repo();
	draw_header_branch();
	draw_header_change();
}
void gitmore::draw_header_repo() {

	int max_repo_name_length = (COLS / 2) - 1;
	std::string repo_name = its_current_repository->get_path().substr(0, max_repo_name_length);

	int repo_name_start_row = 0;
	int repo_name_start_col = 0;
	mvwprintw(its_header_window, repo_name_start_row, repo_name_start_col, repo_name.c_str());

}
void gitmore::draw_header_branch() {

	int max_branch_name_length = (COLS / 2) - 1;
	std::string branch_name = its_current_repository->get_head()->get_short_name().substr(0, max_branch_name_length);

	int branch_name_start_row = 0;
	int branch_name_start_col = (COLS / 2);
	mvwprintw(its_header_window, branch_name_start_row, branch_name_start_col, branch_name.c_str());

}
void gitmore::draw_header_change() {

	int number_length = 3;
	char padding_character = '0';
	const git::status_list& stat = its_current_repository->get_status();

	std::string additions_string = std::to_string(stat.get_num_file_additions());
	additions_string = std::string(number_length - additions_string.length(), padding_character) + additions_string;

	std::string modifications_string = std::to_string(stat.get_num_file_modifications());
	modifications_string = std::string(number_length - modifications_string.length(), padding_character) + modifications_string;

	std::string deletions_string = std::to_string(stat.get_num_file_deletions());
	deletions_string = std::string(number_length - deletions_string.length(), padding_character) + deletions_string;

	std::string change_string = "[ +" + additions_string + "   ~" + modifications_string + "   -" + deletions_string + " ]";

	int change_string_start_row = 1;
	int change_string_start_col = 0;
	mvwprintw(its_header_window, change_string_start_row, change_string_start_col, change_string.c_str());

}