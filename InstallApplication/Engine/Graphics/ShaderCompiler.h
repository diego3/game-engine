#pragma once
#include <string>
#include <iostream>

class ShaderCompiler
{
public:
	static unsigned int Compile(unsigned int type, std::string& shaderCode);

	static unsigned int Create(std::string& vertex, std::string& fragment);

};

