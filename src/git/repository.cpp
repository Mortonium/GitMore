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



		error = git_repository_head(&itsHead, itsRepository);
		if (error == GIT_EUNBORNBRANCH || error == GIT_ENOTFOUND) {
			const git_error *e = giterr_last();
			printf("Error %d/%d: %s\n", error, e->klass, e->message);
			exit(error);
		} else if (!error) {
			itsHeadName = std::string(git_reference_shorthand(itsHead));
		}



		git_reference_iterator * ref_iter = nullptr;
		git_reference_iterator_new(&ref_iter, itsRepository);
		git_reference *ref = NULL;
		while (!(error = git_reference_next(&ref, ref_iter))) {
			if (git_reference_is_branch(ref)) {
				branch* b = new branch(*this, ref);
				itsBranches[b->get_branch_name()] = b;
			} else if (git_reference_is_remote(ref)) {

			} else if (git_reference_is_tag(ref)) {
				
			} // else if (git_reference_is_note(itsReference)) {
			// itsType = type::note;
			// }
		}
		

		/*
		git_status_list* statusList = nullptr;
		git_status_options o = GIT_STATUS_OPTIONS_INIT;
		o.show = GIT_STATUS_SHOW_INDEX_AND_WORKDIR;
		o.flags = GIT_STATUS_OPT_INCLUDE_UNTRACKED |
		GIT_STATUS_OPT_RENAMES_HEAD_TO_INDEX |
		GIT_STATUS_OPT_SORT_CASE_SENSITIVELY;
		git_status_list_new(&statusList, itsCurrentRepo, 0);
		*/

	} else {
		const git_error *e = giterr_last();
		printf("Error %d/%d: %s\n", error, e->klass, e->message);
		exit(error);
	}

}
void git::repository::close() {

	git_repository_free(itsRepository);
	git_reference_free(itsHead);

	itsRepository = nullptr;
	itsHead = nullptr;

	itsPath = "";
	itsHeadName = "";

}

std::string git::repository::get_path() {
	return itsPath;
}





git_repository* git::repository::get_repository() {
	return itsRepository;
}