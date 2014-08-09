#pragma once

#include <git2.h>

#include <string>

#include "repository.hpp"

namespace git {

	class reference {
		friend class git::reference;
		friend class git::repository;

	public:
		enum class type {
			branch,
			note,
			remote,
			tag
		};

		reference(repository& repository);
		reference(repository& repository, std::string name);
		virtual ~reference() = 0;

		int compare(git::reference& other);

		void rename(std::string new_name);

		void delete_reference();

	protected:
		git_reference* get_reference();

	private:
		repository& itsRepository;
		git_reference* itsReference = nullptr;

		git_oid itsOID;
		std::string itsLongName;
		std::string itsShortName;

	};

}