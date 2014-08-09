#pragma once

#include <git2.h>

#include <string>

class Repository {

public:
	Repository();
	Repository(std::string path);
	~Repository();

	void open(std::string path);
	void close();

	std::string getPath();

private:
	git_repository* itsRepository = nullptr;
	git_reference* itsHead = nullptr;

	std::string itsPath;
	std::string itsHeadName;

};