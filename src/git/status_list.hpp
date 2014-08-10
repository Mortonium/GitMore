#pragma once

#include <git2.h>

#include <string>
#include <vector>

#include "status_entry.hpp"

namespace git {

	class status_list {

	public:
		status_list();
		status_list(git_status_list* status_list);
		~status_list();

		void open(git_status_list* status_list);
		void close();

	private:
		git_status_list* its_git_status_list = nullptr;

		std::vector<status_entry*> its_status_entries;

		int its_num_file_additions = 0;
		int its_num_file_modifications = 0;
		int its_num_file_deletions = 0;

	};

}