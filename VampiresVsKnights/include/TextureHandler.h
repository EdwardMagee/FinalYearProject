#pragma once
#include <SFML/Graphics.hpp>
#include <map>
#include <string>
#include <iostream>
#include <vector>

using namespace std;

/*! Singleton that handles all the textures in the game making it possible to get a texture whenever is needed*/

class TextureHandler
{
private:
	map<string, sf::Texture> m_mapOfTextures;  //!< Map holding textures
	static TextureHandler * s_Instance; //!< Create a instance of this 
	TextureHandler(); //!< Constructor
	std::vector<std::string> IDs; //!< A vector containing the ID's of the strings

public:
	~TextureHandler(); //!< Deconstructor
	static TextureHandler * instance();  //!< calling the instance of the class
	void insertTexture(string p_Path, string p_Filename);  //!< add a texture 
														   /*!
														   \param p_Path to get the texture
														   \param p_Filename name of the file
														   */
	sf::Texture getTexture(string p_FileName);  //!< get me the texture
												/*!
												\param p_FileName the name of the file
												*/
	TextureHandler(TextureHandler const&) = delete;  //!< Deletes the assigment operator
	TextureHandler& operator=(TextureHandler const&) = delete; //!< deletes the copy operator
};
