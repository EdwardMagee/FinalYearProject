#include "..\include\FileReaderGameAssests.h"
#include <iostream>

FileReaderGameAssests::FileReaderGameAssests(std::string p_Textures, std::string p_Levels)
{

	std::fstream textureFile(p_Textures, std::ios_base::in);
	std::string textureLine = "";

	if (textureFile.is_open()) {

		while (getline(textureFile, textureLine))
		{
			std::string str;
			std::istringstream isstr(textureLine);
			isstr >> str;

			std::string tempTag; std::string tempFile;

			if (str == "id:") { isstr >> tempTag;	}

			isstr >> str;

			if (str == "file:") { isstr >> tempFile;  }

			m_Textures.push_back(std::make_pair(tempTag, tempFile));
		}
	}
	else {
		std::cout << "cannot open the File" << std::endl;
	}


	std::fstream levelFile(p_Levels, std::ios_base::in);
	std::string levelLine = "";

	if (levelFile.is_open()) {

		while (getline(levelFile, levelLine))
		{
			std::string str; 
			std::istringstream isstr(levelLine);
			isstr >> str;

			std::string tempLevel; std::string tempNodes;

			if (str == "lev:") { isstr >> tempLevel; }

			isstr >> str;

			if (str == "nlev:") { isstr >> tempNodes; }

			m_Levels.push_back(std::make_pair(tempLevel, tempNodes));
		}
	}
	else {
		std::cout << "cannot open the File" << std::endl;
	}

}

std::vector<std::pair<std::string, std::string>> FileReaderGameAssests::getTextures()
{
	return m_Textures;
}

std::vector <std::pair<std::string, std::string>> FileReaderGameAssests::getLevels()
{
	return m_Levels;
}
