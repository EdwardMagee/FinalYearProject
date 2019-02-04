#pragma once
#include <SFML/Graphics.hpp>
#include <map>
#include <string>
#include <iostream>

using namespace std;

class TextureHandler
{
private:
	map<string, sf::Texture> m_mapOfTextures; 
	static TextureHandler * s_Instance; 
	TextureHandler();	

public:
	~TextureHandler(); 
	static TextureHandler * instance(); 
	void insertTexture(string p_Path, string p_Filename); 
	sf::Texture getTexture(string p_FileName); 
	TextureHandler(TextureHandler const&) = delete; 
	TextureHandler& operator=(TextureHandler const&) = delete; 
};
