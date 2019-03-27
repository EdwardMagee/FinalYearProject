#pragma once
#include <SFML/Graphics.hpp>

#include <vector>

class HUD;

/*! This states what every scene should have*/

class SceneInterface 
{
private:


protected:
	virtual void updateScene(float p_time) = 0; //!< Update method
												/*!
												\param p_time contains information on the time
												*/
	virtual bool loadLevel(std::string p_level) = 0; //!< load level
													 /*!
													 \param p_level contains information on the level
													 */
	virtual std::vector<sf::Sprite*> getSpriteVector() = 0; //!< gets a list of sprites
	virtual HUD * getHUD() = 0; //!< Gets the HUD


};