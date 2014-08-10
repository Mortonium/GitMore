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

		branch* get_upstream();

	private:
		branch* itsUpstream = nullptr;

	};

}