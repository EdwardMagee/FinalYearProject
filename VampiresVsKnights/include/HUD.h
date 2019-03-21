#pragma once

#include <SFML/Graphics.hpp>
#include <string>
#include <iostream>

class HUD {

private:

	sf::Font m_Font;
	sf::Text m_Time;
	sf::Text m_Round;
	sf::Text m_Level;
	sf::RectangleShape m_bannerOne;
	sf::RectangleShape m_bannerTwo;

public:

	HUD();

	sf::Text getTime();
	sf::Text getRound();
	sf::Text getLevelText(int p_Level);
	sf::RectangleShape getBannerOne();
	sf::RectangleShape getBannerTwo();

	void setText(float p_time, int p_round);


};