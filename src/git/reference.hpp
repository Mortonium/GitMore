#pragma once

#include <git2.h>

#include <string>

namespace git {

	class reference {

	public:
		enum class type {
			branch,
			note,
			remote,
			tag
		};

		reference();
		reference(std::string name);
		virtual ~reference() = 0;

		int compare(const reference& other);
		int compare(const git_reference* other);

		void rename(std::string new_name);

		void delete_reference();

	protected:
		git_reference* get_reference();

	private:
		git_reference* itsReference;

		git_oid itsOID;
		std::string itsFullName;

	};

}