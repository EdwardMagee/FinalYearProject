#pragma once

#include "SceneInterface.h"
#include <array>
#include <list>
#include <math.h>
#include "SpriteState.h"
#include "GameState.h"
#include "EndState.h"

class TextureHandler;
class SpriteInterface;
class StaticSprite;
class NodeInterface;
class FileReader;
class Graph;
class HUD;

/*! This handles a lot of the game logic, each new scene can have diffrent nodes, characters etc*/

class Scene : public SceneInterface
{
private:
	bool playerkilled; //!< Was a unit killed
	bool m_reachedGoal; //!< Did the unit reach the goal

	TextureHandler * m_textureHandler; //!< Texture Handler 
	FileReader * m_fileReader; //!< File reader
	SpriteInterface* Target; //!< pointer to a target
	
	GameState m_gameState; //!< Stores the games current state
	EndState m_gameOverState; //!< Stores the end state

	sf::Sprite m_selector; //!< Sprite of the selector
	sf::Texture m_selectorTexture; //!< Texture of the selector
	sf::Vector2i m_selectorPos; //!< Position of the selector

	std::vector<SpriteInterface*> m_vectorSprites; //!< A vector of all the sprites
	SpriteInterface* m_playerTemp; //!< stores a temp of the player
	int currentPlayer; //!< What is the current player
	int currentTarget; //!< What is the current target
	int startofKnights; //!< what is the start of the knights in the vector
	int startofVampires; //!< Was a unit killed
	int totalCharacters; //!< How many characters are ther
	bool newcurrentPlayer; //!< is there a new current player
	std::vector<sf::Sprite*> m_vectorTemp; //!< A temp vector containing sprites 
	
	std::list<NodeInterface*> m_pathList; //!< path the unit must take
	NodeInterface* m_prevoiusNode; //!< Pointer to the prevoius node
	NodeInterface * temp; //!< Holds on to a node

	Graph * m_Graph; //!< Game object Graph used to create the grid 
	HUD * m_gameHud; //!< Game object used to display some text to the screen

	int m_round; //!< Stores the current round
	int currentEnemy; //!< What is the current enemy
	float m_time; //!< Stores the time
	float movingCounter; //!< counter used to slow characters down
	
public:

	
	void updateScene(float p_time) override; //!< Update scene
											 /*!
											 \param p_time contains information on the time
											 */
	bool loadLevel(std::string p_level) override; //!< Load level 
												  /*!
												  \param p_level passes in level information
												  */

	std::vector<sf::Sprite*> getSpriteVector() override; //!< Gets a vector of sprites to draw
	
	EndState getEndState(); //!< Gets the scenes end state
	int getRound(); //!< What round is it
	void checkStats(); //!< Display the units stats
	
	sf::Sprite getSelector(); //!< Gets the selector to draw
	void incrementSelector(sf::Vector2i p_newPos); //!< Moves the selector
												   /*!
												   \param p_newPos used to move the selector
												   */
	void decreaseSelector(sf::Vector2i p_newPos); //!< Moves the selector down
												  /*!
												  \param p_newPos used to move the selector
												  */
	void PlayersMove(); //!< When the player hits enter key there move begins
	HUD * getHUD() override; //!< Gets the HUD
	Scene(std::string p_characters, std::string p_nodes); //!< Constructor
														  /*!
														  \param p_characaters contains information the game scharacaters 
														  \param p_nodes contains information the game nodes
														  */
	~Scene(); //!< Deconstructor

};