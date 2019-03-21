#pragma once

#include <fstream>
#include <sstream>
#include <string>
#include <vector>

class FileReaderGameAssests
{
public:

	FileReaderGameAssests(std::string p_Textures, std::string p_Levels);
	std::vector <std::pair<std::string, std::string>> getTextures();
	std::vector <std::pair<std::string, std::string>> getLevels();


private:

	std::vector <std::pair<std::string, std::string>> m_Textures;
	std::vector <std::pair<std::string, std::string>> m_Levels;

};

