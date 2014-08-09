#include "Repository.hpp"

Repository::Repository() {

}
Repository::Repository(std::string path) {
	open(path);
}
Repository::~Repository() {
	if (itsRepository) {
		close();
	}
}

void Repository::open(std::string path) {
	if (itsRepository) {
		close();
	}

	git_repository* newRepo = nullptr;
	int error = git_repository_open(&newRepo, path.c_str());
	if (!error) {
		itsRepository = newRepo;
		itsPath = path;
		
		/*
		int error = 0;
		git_reference *head = NULL;

		error = git_repository_head(&head, itsCurrentRepo);

		if (error == GIT_EUNBORNBRANCH || error == GIT_ENOTFOUND)
			itsCurrentBranch = "";
		else if (!error) {
			itsCurrentBranch = std::string(git_reference_shorthand(head));
		}

		git_reference_free(head);
		*/

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

	}

}
void Repository::close() {
	git_repository_free(itsRepository);
	itsPath = "";
	itsRepository = nullptr;
}

std::string Repository::getPath() {
	return itsPath;
}