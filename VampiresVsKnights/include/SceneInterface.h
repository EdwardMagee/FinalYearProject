/**
@file SceneInterface
@brief blueprint's on how every scene should be set
*/

#pragma once
#include <SFML/Graphics.hpp>

#include <vector>

class HUD;

/*! This states what every scene should have*/

/*! \class SceneInterface
	\brief blueprint's on how every scene should be set and what method's it should use
*/


class SceneInterface 
{
private:


protected:

	/*!
	\brief updates elements within the scene
    \param p_time contains information on the time
	*/

	virtual void updateScene(float p_time) = 0; 

	/*!
	\brief load's data from files
	\param p_level contains information on the level
	*/
												
	virtual bool loadLevel(std::string p_level) = 0; 

	/*!
	\brief get's the spirtes used later to render them
	*/

	virtual std::vector<sf::Sprite*> getSpriteVector() = 0; 

	/*!
	\brief get's the HUD, used later to render it it or change an element within the object
	*/

	virtual HUD * getHUD() = 0; 


};