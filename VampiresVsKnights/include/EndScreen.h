#pragma once
#pragma once

#include "GameInterface.h"
#include <vector>
#include <string>

/*! The screen that will come at the end showing the user the time and rounds*/

class TextureHandler;

class EndScreen : public GameInterface
{

public:

	EndScreen(std::string p_rounds, std::string p_time, std::string p_text); //!< Constructs the end screen
																			 /*!
																			 \param p_rounds contains the string for text
																			 \param p_time contains string text
																			 \param p_text contains text to be added to the screen
																			 */
	~EndScreen(); //!< Deconstructor

	void updateGame(float p_time) override; //!< Updates the EndScreen
											/*!
											\param p_time contains information on the time
											*/

	void draw(sf::RenderTarget& target, sf::RenderStates states) const override; //!< draws the end screen
																				 /*!
																				 \param target draw this 
																				 \param states paramater needed for the draw method
																				 */
	void handleInput(int p_InputEvent) override; //!< Handles the 
												 /*!
												 \param p_InputEvent information needed to know what key is pressed
												 */

	virtual EndState isOver() override; //!< Returns the end state of the class
	virtual void loadLevel() override; //!< interface demands this to be here needed in other classes


private:
	
	TextureHandler * m_textures; //!< Gets the textures

	EndState m_over; //!< stores the end screen state

	sf::Font m_font; //!< Stores the font
	sf::Text m_roundText; //!< used to display what round the player was on to the screen
	sf::Text m_timeText; //!< Displays the time
	sf::Text m_screenText; //!< Displays text to the end screen

	sf::Sprite m_sBackground; //!< The Background sprite of the end screen
	sf::Texture m_tBackground; //!< Texture of the background


};
