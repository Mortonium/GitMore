#pragma once

#include <git2.h>

#include "diff_delta.hpp"

namespace git{

	class status_entry {

	public:
		enum class type {
			current = 0,

			index_new = (1u << 0),
			index_modified = (1u << 1),
			index_deleted = (1u << 2),
			index_renamed = (1u << 3),
			index_typechange = (1u << 4),

			wt_new = (1u << 7),
			wt_modified = (1u << 8),
			wt_deleted = (1u << 9),
			wt_typechange = (1u << 10),
			wt_renamed = (1u << 11),

			ignored = (1u << 14),
		};

		status_entry();
		status_entry(const git_status_entry* status_entry);
		~status_entry();

		type get_type();

	private:
		type its_type;
		diff_delta* its_head_to_index = nullptr;
		diff_delta* its_index_to_workdir = nullptr;

	};

}