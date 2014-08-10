#include "status_list.hpp"

#include "status_entry.hpp"

git::status_list::status_list() {

}
git::status_list::status_list(git_status_list* status_list) {
	open(status_list);
}
git::status_list::~status_list() {
	close();
}

void git::status_list::open(git_status_list* status_list) {
	
	its_git_status_list = status_list;
	its_num_file_additions = 0;
	its_num_file_modifications = 0;
	its_num_file_deletions = 0;

	size_t count = git_status_list_entrycount(status_list);
	for (size_t i = 0; i < count; ++i) {
		const git_status_entry *git_entry = git_status_byindex(status_list, i);
		status_entry* entry = new status_entry(git_entry);
		switch (entry->get_type()) {

		case status_entry::type::current:
			break;

		case status_entry::type::index_new:
		case status_entry::type::wt_new:
			its_num_file_additions++;
			break;

		case status_entry::type::index_modified:
		case status_entry::type::wt_modified:
			its_num_file_modifications++;
			break;

		case status_entry::type::index_deleted:
		case status_entry::type::wt_deleted:
			its_num_file_deletions++;
			break;

		default: break;
		}
		its_status_entries.push_back(entry);
	}

}
void git::status_list::close() {
	if (its_git_status_list)
		git_status_list_free(its_git_status_list);
}