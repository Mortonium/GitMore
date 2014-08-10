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
	void wait_for_thread_finish();

	gitmore_state get_state() const;

	void key_press(int chr);



private:
	std::thread* its_thread = nullptr;
	std::atomic<gitmore_state> its_state{ gitmore_state::none };
	git::repository* its_current_repository = nullptr;
	Settings its_settings;

	std::queue<int> its_input_queue;
	std::mutex its_input_queue_mutex;

	CLI its_CLI;



	void set_state(gitmore_state s);

	void main();
	void interpret_key_press(int ch);

	void set_current_repo(std::string path);
	void close_current_repo();

	void execute_command_string(std::string command_string);
	void interpret_command(std::string command_string);

	void draw();

};