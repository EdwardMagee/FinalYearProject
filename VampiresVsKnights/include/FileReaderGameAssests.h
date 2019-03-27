#pragma once

#include <fstream>
#include <sstream>
#include <string>
#include <vector>

/*! Another file reader with the purpose of loading in textures and levels*/

class FileReaderGameAssests
{
public:

	FileReaderGameAssests(std::string p_Textures, std::string p_Levels); //!< Constructor for the class
																		 /*!
																		 \param p_Textures string containing information on where to find the texture file
																		 \param p_Levels another string that when read gives data from the levels file
																		 */

	std::vector <std::pair<std::string, std::string>> getTextures(); //!< a vector of a pair of strings that gets all the containing all the texture information
	std::vector <std::pair<std::string, std::string>> getLevels(); //!< a vector of a pair of strings which get level information inside of them


private:

	std::vector <std::pair<std::string, std::string>> m_Textures; //!< stores a vector of textures 
	std::vector <std::pair<std::string, std::string>> m_Levels; //!< stores a vector of levels

};

