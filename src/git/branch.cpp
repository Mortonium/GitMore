#include "branch.hpp"

git::branch::branch(repository& repo) : reference(repo) {

}
git::branch::branch(repository& repo, git_reference* ref) : reference(repo, ref) {
	
	if (!git_reference_is_branch(ref)) {
		// Bad times
		printf("Branch not a branch\n");
		exit(1);
	} else {
		
	}

}

git::branch* git::branch::get_upstream() {
	return itsUpstream;
}