#pragma once

#include <SFML/Graphics.hpp>
#include <string>
#include <iostream>

class HUD {

private:

	sf::Font m_Font;
	sf::Text m_Time;
	sf::Text m_Round;

public:

	HUD();

	sf::Text getTime();
	sf::Text getRound();

	void setText(float p_time, int p_round);


};