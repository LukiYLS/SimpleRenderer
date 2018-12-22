
#include "UtilsHelp.h"
#include<iostream>
#include<string>
namespace SRE
{

	std::string StringHelp::Int2String(unsigned int a)
	{
		std::stringstream ss;
		std::string number;
		ss << a;
		ss >> number;
		return number;
	}
	std::string StringHelp::readFileToStr(const char* fileName)
	{
		std::string result;
		std::ifstream shaderFile;
		std::cout << std::string(fileName);
		if(!shaderFile.is_open())
			std::cout << "cannot open file";
		shaderFile.open(fileName);

		std::stringstream shaderStream;

		shaderStream << shaderFile.rdbuf();
		shaderStream >> result;

		shaderFile.close();

		return shaderStream.str();
	}
}

