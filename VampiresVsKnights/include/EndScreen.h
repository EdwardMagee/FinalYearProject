#pragma once
#pragma once

#include "GameInterface.h"
#include <vector>
#include <string>

class TextureHandler;

class EndScreen : public GameInterface
{

public:

	EndScreen(std::string p_rounds, std::string p_time, std::string p_text);
	~EndScreen();

	void updateGame(float p_time) override;
	void draw(sf::RenderTarget& target, sf::RenderStates states) const override;
	void handleInput(int p_InputEvent) override;
	virtual EndState isOver() override;
	virtual void loadLevel() override;


private:
	
	TextureHandler * m_textures;

	EndState m_over;

	sf::Font m_font;
	sf::Text m_roundText;
	sf::Text m_timeText;
	sf::Text m_screenText;

	sf::Sprite m_sBackground;
	sf::Texture m_tBackground;


};
