#pragma once

#include <cstdint>
#include <string>

#include <git2.h>

namespace git {

	typedef std::int64_t offset_t;

	class diff_file {

	public:
		diff_file();
		diff_file(const git_diff_file& diff);

		git_oid get_oid();
		std::string get_path();
		git_off_t get_size();
		uint32_t get_flags();
		uint16_t get_mode();

	private:
		git_oid     its_oid;
		std::string its_path;
		git_off_t   its_size;
		uint32_t    its_flags;
		uint16_t    its_mode;

	};



	class diff_delta {

	public:
		enum class type {
			unmodified = 0, /** no changes */
			added = 1,      /** entry does not exist in old version */
			deleted = 2,    /** entry does not exist in new version */
			modified = 3,   /** entry content changed between old and new */
			renamed = 4,    /** entry was renamed between old and new */
			copied = 5,     /** entry was copied from another old entry */
			ignored = 6,    /** entry is ignored item in workdir */
			untracked = 7,  /** entry is untracked item in workdir */
			typechange = 8, /** type of entry changed between old and new */
		};

		diff_delta();
		diff_delta(git_diff_delta* diff);

	private:
		type      its_type;
		uint32_t  its_flags;      /**< git_diff_flag_t values */
		uint16_t  its_similarity; /**< for RENAMED and COPIED, value 0-100 */
		uint16_t  its_nfiles;     /**< number of files in this delta */
		diff_file its_old_file;
		diff_file its_new_file;
	
	};

}