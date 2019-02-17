#include "..\include\TextureHandler.h"

TextureHandler * TextureHandler::s_Instance = nullptr;

TextureHandler::TextureHandler() {
}

TextureHandler::~TextureHandler() {
}

void TextureHandler::insertTexture(string p_path, string p_filename)
{

	sf::Texture temp;
	temp.loadFromFile(p_filename);
	m_mapOfTextures.insert(pair<string, sf::Texture>(string(p_path), sf::Texture(temp))); 
	IDs.push_back(p_path);

}

sf::Texture TextureHandler::getTexture(string p_FileName)
{
	sf::Texture temptexture;

	for (int i = 0; IDs.size() > i; i++)
	{
		if (IDs.at(i) == p_FileName)
		{
			temptexture = m_mapOfTextures.at(p_FileName);
			return temptexture;
		}
	}
		
	std::cout << "Texture Does not Exist, Did you type it Wrong?!" << endl;
	return temptexture;
	
}


TextureHandler * TextureHandler::instance()
{
	if (s_Instance == nullptr)
	{
		s_Instance = new TextureHandler();
	}
	return s_Instance;
}
