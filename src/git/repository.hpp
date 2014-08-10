#pragma once

#include <git2.h>

#include <string>
#include <vector>
#include <map>

#include "status_list.hpp"

namespace git {

	class branch;

	class repository {
		friend class reference;

	public:
		repository();
		repository(std::string path);
		~repository();

		void open(std::string path);
		void close();

		std::string get_path();
		const branch* get_head();

	private:
		git_repository* itsRepository = nullptr;

		std::string itsPath;
		branch* its_head = nullptr;
		std::map<std::string, branch*> itsBranches;
		status_list itsStatusList;

		git_repository* get_repository();

	};

}