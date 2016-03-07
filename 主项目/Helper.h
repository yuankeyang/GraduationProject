#pragma once

#include <string>
#include <vector>
#include <sstream>

class Helper
{
public:
	Helper();
	~Helper();
	static std::vector<std::string> &split(const std::string&, char, std::vector<std::string>&);
	static std::vector<std::string> split(const std::string&, char);
};

