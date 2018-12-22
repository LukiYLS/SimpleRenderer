#pragma once
#include <fstream>
#include <sstream>
#include <algorithm>
#include <string>

namespace SRE {

	class StringHelp {
	public:
		static std::string Int2String(unsigned int a);
		static std::string readFileToStr(const char* fileName);
	};

	
	
}