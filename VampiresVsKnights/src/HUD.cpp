#include "..\include\HUD.h"

HUD::HUD()
{
	if (!m_Font.loadFromFile("../VampiresVsKnights/Assests/Fonts/ariblk.ttf"))     
	{
		std::cout << "Unable to load Font" << std::endl;
	}

	m_Time.setFont(m_Font); m_Round.setFont(m_Font);
	m_Time.setCharacterSize(15), m_Round.setCharacterSize(15);
	m_Time.setPosition(0, 1), m_Round.setPosition(300, 1);

}

sf::Text HUD::getTime()
{
	return m_Time; 
}

sf::Text HUD::getRound()
{
	return m_Round;
}

void HUD::setText(float p_time, int p_round)
{
	m_Time.setString("Time : " + std::to_string((int)p_time));
	m_Round.setString("Round : " + std::to_string(p_round));

}
