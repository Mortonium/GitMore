#pragma once

#include <git2.h>

#include <string>

#include "reference.hpp"

namespace git {

	class repository;

	class branch : public reference {

	public:
		branch(repository& repo);
		branch(repository& repo, git_reference* ref);

		std::string get_branch_name();
		branch* get_upstream();

	private:
		std::string itsBranchName;
		branch* itsUpstream = nullptr;

	};

}