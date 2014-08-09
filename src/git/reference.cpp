#include "reference.hpp"

git::reference::reference(repository& repository) : itsRepository(repository) {
	
}
git::reference::reference(repository& repository, std::string name) : itsRepository(repository) {
	
	int error = git_reference_lookup(&itsReference, itsRepository.get_repository(), name.c_str());

	if (error == GIT_EINVALIDSPEC)
		error = git_reference_dwim(&itsReference, itsRepository.get_repository(), name.c_str());
	
	if (!error) {
		itsLongName = std::string(git_reference_name(itsReference));
		itsShortName = std::string(git_reference_shorthand(itsReference));
		git_reference_name_to_id(&itsOID, itsRepository.get_repository(), itsLongName.c_str());
		if (git_reference_is_branch(itsReference))
			itsType = type::branch;
		// else if (git_reference_is_note(itsReference))
			// itsType = type::note;
		else if (git_reference_is_remote(itsReference))
			itsType = type::remote;
		else if (git_reference_is_tag(itsReference))
			itsType = type::tag;
	} else {
		const git_error *e = giterr_last();
		printf("Error %d/%d: %s\n", error, e->klass, e->message);
		exit(error);
	}

}
git::reference::~reference() {
	if (itsReference)
		git_reference_free(itsReference);
}

git::reference::type git::reference::get_type() {
	return itsType;
}
std::string git::reference::get_long_name() const {
	return itsLongName;
}
std::string git::reference::get_short_name() const {
	return itsShortName;
}

int git::reference::compare(git::reference& other) {
	return git_reference_cmp(this->get_reference(), other.get_reference());
}

void git::reference::rename(std::string new_name) {

}

void git::reference::delete_reference() {

}

git_reference* git::reference::get_reference() {
	return itsReference;
}