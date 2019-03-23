#pragma once

#include "GameInterface.h"
#include <vector>

class TextureHandler;
class FileReaderGameAssests;

class MenuOne : public GameInterface
{

public:

	MenuOne();
	~MenuOne();

	void updateGame(float p_time) override;
    void draw(sf::RenderTarget& target, sf::RenderStates states) const override;
	void handleInput(int p_InputEvent) override;
	virtual bool isOver() override;
	virtual void loadLevel() override;
	int getLevel();


private:
	FileReaderGameAssests * m_reader;

	sf::Sprite m_sBackground;
	sf::Texture m_tBackground;

	std::vector<sf::Sprite*> m_sButtons;
	sf::Texture m_tButtons;

	sf::Sprite m_sSelector;
	sf::Texture m_tSelector;

	sf::Font m_font;
	sf::Text m_menuText;
	std::vector<sf::Text*> m_buttonText;

	TextureHandler * m_textures;

	int m_currentLevel;
	bool m_over;


};
