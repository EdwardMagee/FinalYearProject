#include "..\include\EndScreen.h"
#include "..\include\TextureHandler.h"

EndScreen::EndScreen(std::string p_rounds, std::string p_time, std::string p_text)
{
	if (!m_font.loadFromFile("../VampiresVsKnights/Assests/Fonts/ariblk.ttf"))
	{
		std::cout << "Unable to load Font" << std::endl;
	}

	m_over = EndState::Defualt;

	m_tBackground = m_textures->instance()->getTexture("End");
	m_sBackground.setTexture(m_tBackground);
	m_sBackground.setPosition(sf::Vector2f(0, 0));
	m_sBackground.scale(sf::Vector2f(1.5, 2.0));


	m_roundText.setFont(m_font); m_screenText.setFont(m_font); m_timeText.setFont(m_font);
	m_roundText.setCharacterSize(25); m_screenText.setCharacterSize(25); m_timeText.setCharacterSize(25);
	m_roundText.setPosition(150, 400); m_screenText.setPosition(100, 100); m_timeText.setPosition(150, 450);
	m_roundText.setString(p_rounds); m_screenText.setString(p_text); m_timeText.setString(p_time); 


}

EndScreen::~EndScreen()
{
}

void EndScreen::updateGame(float p_time)
{
}

void EndScreen::draw(sf::RenderTarget & target, sf::RenderStates states) const
{
	target.draw(m_sBackground);
	target.draw(m_roundText);
	target.draw(m_screenText);
	target.draw(m_timeText);
}

void EndScreen::handleInput(int p_InputEvent)
{

	switch (p_InputEvent)
	{
		case sf::Keyboard::Escape:
		{
		m_over = EndState::EndMenu;
		break;
		}

		case sf::Keyboard::Enter:
		{
		m_over = EndState::EndMenu;
		break;
		}
	}
}


EndState EndScreen::isOver()
{
	return m_over;
}

void EndScreen::loadLevel()
{
}
