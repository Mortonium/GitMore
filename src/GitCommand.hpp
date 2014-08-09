#pragma once

#include <string>
#include <map>
#include <vector>

/*



git init [-q | --quiet] [--bare] [--template=<template_directory>]
[--separate-git-dir <git dir>]
[--shared[=<permissions>]] [directory]



git clone [--template=<template_directory>]
[-l] [-s] [--no-hardlinks] [-q] [-n] [--bare] [--mirror]
[-o <name>] [-b <name>] [-u <upload-pack>] [--reference <repository>]
[--separate-git-dir <git dir>]
[--depth <depth>] [--[no-]single-branch]
[--recursive | --recurse-submodules] [--] <repository>
[<directory>]



git add [-n] [-v] [--force | -f] [--interactive | -i] [--patch | -p]
	[--edit | -e] [--[no-]all | --[no-]ignore-removal | [--update | -u]]
	[--intent-to-add | -N] [--refresh] [--ignore-errors] [--ignore-missing]
	[--] [<pathspec>...]



git status [<options>...] [--] [<pathspec>...]



git diff [options] [<commit>] [--] [<path>...]
git diff [options] --cached [<commit>] [--] [<path>...]
git diff [options] <commit> <commit> [--] [<path>...]
git diff [options] <blob> <blob>
git diff [options] [--no-index] [--] <path> <path>



git commit [-a | --interactive | --patch] [-s] [-v] [-u<mode>] [--amend]
[--dry-run] [(-c | -C | --fixup | --squash) <commit>]
[-F <file> | -m <msg>] [--reset-author] [--allow-empty]
[--allow-empty-message] [--no-verify] [-e] [--author=<author>]
[--date=<date>] [--cleanup=<mode>] [--[no-]status]
[-i | -o] [-S[<keyid>]] [--] [<file>...]



git reset [-q] [<tree-ish>] [--] <paths>...
git reset (--patch | -p) [<tree-ish>] [--] [<paths>...]
git reset [--soft | --mixed | --hard | --merge | --keep] [-q] [<commit>]



git rm [-f | --force] [-n] [-r] [--cached] [--ignore-unmatch] [--quiet] [--] <file>...



git mv [-v] [-f] [-n] [-k] <source> <destination>
git mv [-v] [-f] [-n] [-k] <source> ... <destination directory>



*/

class GitCommandArgumentComponent {



};

class GitCommandArgument : public GitCommandArgumentComponent {

private:
	std::string itsName;
	bool itsRequired;

};

class GitCommandArgumentWithParameters : public GitCommandArgument {

private:
	std::vector<GitCommandArgumentComponent*> itsParameters;

};

class GitCommandOptArgumentList : public GitCommandArgumentComponent {

private:


};

class GitCommand {

public:

private:
	std::string itsCommandName;
	std::vector<GitCommandArgumentComponent*> itsArguments;
	//std::map<std::string, GitCommand*> itsSubCommands;
	//std::map<std::string, GitCommandArgument> itsArguments;

};

class GitCommand_add {

	

};