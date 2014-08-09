#pragma once

#include <git2.h>

#include <string>

#include "reference.hpp"

namespace git {

	class branch : public reference {

	public:
		branch();

	};

}