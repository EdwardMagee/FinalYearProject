#pragma once

#include "GameInterface.h" 
#include <fstream>
#include <sstream>
#include <vector>
#include <string>

class Scene;
class TextureHandler;
class FileReaderGameAssests;

class GameOne : public GameInterface
{
private:

	FileReaderGameAssests * m_reader;
	Scene * m_currentScene;
	TextureHandler * m_textureHandler;
	sf::Sprite m_backgroundSprite;
	sf::Texture m_backgroundTexture;
	//std::vector<std::string> m_vectorLevels;
	std::vector <std::pair<std::string, std::string>> m_vectorLevels;
	bool m_over;
	int m_Level;

public:
	GameOne();
	~GameOne();
	void insertTextures();
	void updateGame(float p_time) override;
	void draw(sf::RenderTarget& target, sf::RenderStates states) const override;
	void handleInput(int p_InputEvent) override;
	bool isOver() override;
	void loadLevel() override;
	

};