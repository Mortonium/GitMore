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