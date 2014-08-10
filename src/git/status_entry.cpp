#include "status_entry.hpp"

git::status_entry::status_entry() {

}
git::status_entry::status_entry(const git_status_entry* status_entry) {

	its_type = static_cast<type>(status_entry->status);

	if (status_entry->head_to_index)
		its_head_to_index = new diff_delta(status_entry->head_to_index);

	if (status_entry->index_to_workdir)
		its_index_to_workdir = new diff_delta(status_entry->index_to_workdir);

}
git::status_entry::~status_entry() {
	if (its_head_to_index)
		delete its_head_to_index;
	if (its_index_to_workdir)
		delete its_index_to_workdir;
}