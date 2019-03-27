#pragma once
#include <SFML/Graphics.hpp>
#include "EndState.h"

/*! An interface class used for each window origanlly ment to be just for the game but it had values the menu's could use */

class GameInterface : public sf::Drawable
{
private:


protected:
	virtual void updateGame(float p_time) = 0; //!< Every game needs to be updated
											   /*!
											   \param p_time contains information on the time
											   */
	virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const = 0; //!< Every game needs to be drawn
																					/*!
																					\param target draw this
																					\param states paramater needed for the draw method
																					*/
	virtual void handleInput(int p_InputEvent) = 0; //!< Every game needs key inputs
													/*!
													\param p_InputEvent information needed to know what key is pressed
													*/
	virtual EndState isOver() = 0; //!< Every game needs an end state
	virtual void loadLevel() = 0; //!< Every game needs to be loaded

};