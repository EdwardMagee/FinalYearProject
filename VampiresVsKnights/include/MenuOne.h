#pragma once

#include "GameInterface.h"
#include <vector>

class TextureHandler;
class FileReaderGameAssests;

/*! This class is used for the starting menu's it allows the user what level they want to play*/

class MenuOne : public GameInterface
{

public:

	MenuOne(); //!< Constructor
	~MenuOne(); //!< Deconstructor 

	void updateGame(float p_time) override; //!< update the menu
											/*!
											\param p_time contains information on the time
											*/
    void draw(sf::RenderTarget& target, sf::RenderStates states) const override; //!< draw the menu
																				 /*!
																				 \param target draw this
																				 \param states paramater needed for the draw method
																				 */
	void handleInput(int p_InputEvent) override; //!< Handles menu input
												 /*!
												 \param p_InputEvent information needed to know what key is pressed
												 */
	virtual EndState isOver() override; //!< What is the end stae
	virtual void loadLevel() override; //!< Load the level
	int getLevel(); //!< Get the level


private:
	FileReaderGameAssests * m_reader; //!< Game Assests reader

	sf::Sprite m_sBackground; //!< Backround
	sf::Texture m_tBackground; //!< Texture of background

	std::vector<sf::Sprite*> m_sButtons;//!< Buttons on the menu
	sf::Texture m_tButtons; //!< Texture of those buttons

	sf::Sprite m_sSelector; //!< The selector changing what the button looks like
	sf::Texture m_tSelector; //!< Texture of the changer 

	sf::Font m_font; //!< Menu Font
	sf::Text m_menuText; //!< Text on the menu
	std::vector<sf::Text*> m_buttonText; //!< Text in the button

	TextureHandler * m_textures; //!< Texture Handler

	int m_currentLevel;//!< Stores the current level
	EndState m_over; //!< End state is stored here


};
