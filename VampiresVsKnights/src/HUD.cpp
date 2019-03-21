#include "..\include\HUD.h"

HUD::HUD()
{
	if (!m_Font.loadFromFile("../VampiresVsKnights/Assests/Fonts/ariblk.ttf"))     
	{
		std::cout << "Unable to load Font" << std::endl;
	}

	m_Time.setFont(m_Font); m_Round.setFont(m_Font); m_Level.setFont(m_Font);
	m_Time.setCharacterSize(19), m_Round.setCharacterSize(19); m_Level.setCharacterSize(19);
	m_Time.setPosition(20, 20), m_Round.setPosition(270, 20); m_Level.setPosition(140, 20);

	m_bannerOne.setSize(sf::Vector2f(392, 50)); m_bannerTwo.setSize(sf::Vector2f(400, 60));
	m_bannerOne.setPosition(sf::Vector2f(0, 13)); m_bannerTwo.setPosition(sf::Vector2f(0, 9));
	m_bannerOne.setFillColor(sf::Color::Black); m_bannerTwo.setFillColor(sf::Color::Cyan);

}

sf::Text HUD::getTime()
{
	return m_Time; 
}

sf::Text HUD::getRound()
{
	return m_Round;
}

sf::Text HUD::getLevelText(int p_Level)
{
	m_Level.setString("Level : " + std::to_string(p_Level));
	return m_Level;
}

sf::RectangleShape HUD::getBannerOne()
{
	return m_bannerOne;
}

sf::RectangleShape HUD::getBannerTwo()
{
	return m_bannerTwo;
}

void HUD::setText(float p_time, int p_round)
{
	m_Time.setString("Time : " + std::to_string((int)p_time));
	m_Round.setString("Round : " + std::to_string(p_round));

}
