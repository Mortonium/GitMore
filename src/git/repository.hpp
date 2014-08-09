#pragma once

#include <git2.h>

#include <string>
#include <vector>

namespace git {

	class reference;

	class repository {
		friend class reference;

	public:
		repository();
		repository(std::string path);
		~repository();

		void open(std::string path);
		void close();

		std::string get_path();

	private:
		git_repository* itsRepository = nullptr;
		git_reference* itsHead = nullptr;

		std::string itsPath;
		std::string itsHeadName;
		std::vector<reference*> itsReferences;

		git_repository* get_repository();

	};

}