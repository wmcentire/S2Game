#pragma once
#include <string>

namespace pb {

	class Resource {
	public:
		virtual bool Create(std::string filename, ...) = 0;
	};


}