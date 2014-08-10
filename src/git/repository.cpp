#include "repository.hpp"

#include "branch.hpp"

git::repository::repository() {

}
git::repository::repository(std::string path) {
	open(path);
}
git::repository::~repository() {
	if (itsRepository) {
		close();
	}
}

void git::repository::open(std::string path) {
	if (itsRepository) {
		close();
	}

	int error = git_repository_open(&itsRepository, path.c_str());
	if (!error) {

		itsPath = path;



		// Iterate and interpret all references
		git_reference_iterator* ref_iter = nullptr;
		git_reference_iterator_new(&ref_iter, itsRepository);
		git_reference* ref = NULL;
		while (!(error = git_reference_next(&ref, ref_iter))) {
			if (git_reference_is_branch(ref)) {
				branch* b = new branch(*this, ref);
				itsBranches[b->get_short_name()] = b;
				if (git_branch_is_head(ref)) {
					its_head = b;
				}
			} else if (git_reference_is_remote(ref)) {

			} else if (git_reference_is_tag(ref)) {
				
			} // else if (git_reference_is_note(itsReference)) {
			// itsType = type::note;
			// }
		}

		git_reference_iterator_free(ref_iter);
		


		
		git_status_list* g_status_list = nullptr;
		git_status_options o = GIT_STATUS_OPTIONS_INIT;
		o.show = GIT_STATUS_SHOW_INDEX_AND_WORKDIR;
		o.flags = GIT_STATUS_OPT_INCLUDE_UNTRACKED | GIT_STATUS_OPT_RENAMES_HEAD_TO_INDEX | GIT_STATUS_OPT_SORT_CASE_SENSITIVELY;
		git_status_list_new(&g_status_list, itsRepository, 0);

		itsStatusList = status_list(g_status_list);

	} else {
		const git_error *e = giterr_last();
		printf("Error %d/%d: %s\n", error, e->klass, e->message);
		exit(error);
	}

}
void git::repository::close() {

	git_repository_free(itsRepository);

	itsRepository = nullptr;

	itsPath = "";
	its_head = nullptr;

}

std::string git::repository::get_path() {
	return itsPath;
}
const git::branch* git::repository::get_head() {
	return its_head;
}





git_repository* git::repository::get_repository() {
	return itsRepository;
}