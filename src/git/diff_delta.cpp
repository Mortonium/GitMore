#include "diff_delta.hpp"

git::diff_file::diff_file() {

}
git::diff_file::diff_file(const git_diff_file& diff) {
	its_oid = diff.oid;
	its_path = std::string(diff.path);
	its_size = diff.size;
	its_flags = diff.flags;
	its_mode = diff.mode;
}

git_oid git::diff_file::get_oid() {
	return its_oid;
}
std::string git::diff_file::get_path() {
	return its_path;
}
git_off_t git::diff_file::get_size() {
	return its_size;
}
uint32_t git::diff_file::get_flags() {
	return its_flags;
}
uint16_t git::diff_file::get_mode() {
	return its_mode;
}



git::diff_delta::diff_delta() {

}
git::diff_delta::diff_delta(git_diff_delta* diff) {
	its_type       = static_cast<type>(diff->status);
	its_flags      = diff->flags;
	its_similarity = diff->similarity;
	its_nfiles     = diff->nfiles;
	its_old_file   = diff_file(diff->old_file);
	its_new_file   = diff_file(diff->new_file);
}