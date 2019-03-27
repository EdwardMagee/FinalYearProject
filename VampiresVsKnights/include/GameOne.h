#pragma once

#include "GameInterface.h" 
#include <fstream>
#include <sstream>
#include <vector>
#include <string>

class Scene;
class TextureHandler;
class FileReaderGameAssests;

/*! This class is is to run the game */

class GameOne : public GameInterface
{
private:

	FileReaderGameAssests * m_reader; //!< Used to load in game assessts
	Scene * m_currentScene; //!< Current scene of the game
	TextureHandler * m_textureHandler; //!< handles the textures
	sf::Sprite m_backgroundSprite; //!< The Background sprite
	sf::Texture m_backgroundTexture; //!< Background texture
	std::vector <std::pair<std::string, std::string>> m_vectorLevels; //!< Stores the games level
	EndState m_endState; //!< Stores the end game state
	int m_Level; //!< What level is the game currently on

public:
	GameOne(int p_level); //!< Constructor 
						  /*!
						  \param p_level passes in what level should be loaded
						  */
	~GameOne(); //!< Deconstructor
	void updateGame(float p_time) override; //!< updates the game
	void draw(sf::RenderTarget& target, sf::RenderStates states) const override; //!< draw game
																				 /*!
																				 \param target draw this
																				 \param states paramater needed for the draw method
																				 */
	void handleInput(int p_InputEvent) override; //!< Handles the inputs of the game
												 /*!
												 \param p_InputEvent information needed to know what key is pressed
												 */
	EndState isOver() override; //!< What state is the end state
	void loadLevel() override;//!< load the level
	Scene * getScene(); //!< get the scene
	

};