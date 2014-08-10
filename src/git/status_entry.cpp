#include "status_entry.hpp"

git::status_entry::status_entry() {

}
git::status_entry::status_entry(const git_status_entry* status_entry) {
	itsType = static_cast<type>(status_entry->status);
}