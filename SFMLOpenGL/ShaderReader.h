#ifndef SHADER_READER_H
#define SHADER_READER_H

#include <string>
#include <iostream>
#include <fstream>

class ShaderReader
{
public:
	static std::string readFile(const std::string t_fileName);
};

#endif // !SHADER_READER_H