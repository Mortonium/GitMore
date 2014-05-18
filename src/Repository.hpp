#pragma once

#include <git2.h>

#include <string>

class Repository {

public:
	Repository();
	Repository(std::string path);
	~Repository();

	void open(std::string path);

	std::string getPath();

private:
	git_repository* itsRepository = nullptr;

	std::string itsPath;

};