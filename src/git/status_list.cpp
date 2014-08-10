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
	size_t count = git_status_list_entrycount(status_list);
	for (size_t i = 0; i < count; ++i) {
		const git_status_entry *entry = git_status_byindex(status_list, i);
		its_status_entries.push_back(new status_entry(entry));
	}
}
void git::status_list::close() {
	if (its_git_status_list)
		git_status_list_free(its_git_status_list);
}