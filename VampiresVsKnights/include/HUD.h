#pragma once

#include <SFML/Graphics.hpp>
#include <string>
#include <iostream>

/*! Used to render text to the screen informing the user on game features*/

class HUD {

private:

	sf::Font m_Font; //!< Font for Hud
	sf::Text m_Time; //!< Stores the text for time
	sf::Text m_Round; //!< Stores text for rounds
	sf::Text m_Level; //!< Stores text of level
	sf::RectangleShape m_bannerOne; //!< banner one
	sf::RectangleShape m_bannerTwo; //!< banner two

public:

	HUD(); //!< Constructor 

	sf::Text getTime(); //!< Gets the text for time
	sf::Text getRound(); //!< Gets the text for rounds
	sf::Text getLevelText(int p_Level); //!< get the level text
										/*!
										\param p_Level neded to know what level is being shown
										*/
	sf::RectangleShape getBannerOne(); //!< gets Banner one to be drawn
	sf::RectangleShape getBannerTwo(); //!< gets banner two

	void setText(float p_time, int p_round); //!< Set the text of the banner
											 /*!
											 \param p_time contains information on the time
											 \param p_round contains information on the round
											 */


};