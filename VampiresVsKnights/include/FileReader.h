#pragma once
#include <fstream>
#include <sstream>
#include <SFML/Graphics.hpp>
#include <string>
#include <vector>

/*! File Reader that is used to load in characters and there stats*/

class FileReader 
{
public:
	~FileReader(); //!< Deconstructor
	FileReader(std::string p_level); //!< Constructor the File counts as its own object
									 /*!
									 \param p_level dt used to tell the change in time
									 */	

	std::vector<float> getSpeedValues(); //!< a get method that returns a vector of floats used to give characters their speed value
	std::vector<sf::Vector2i> getPositions(); //!< used to get all the characters positions within the grid
	std::vector<float> getHealth(); //!< gets all the characters health's
	std::vector<float> getAttack(); //!< gets all the characaters attack stats 
	std::vector<std::string> getTexture(); //!< This tells the character what its texture is
	int getStartOfVamps(); //!< tells the scene when the vampires start in the vector

protected:

	std::vector<float> m_speedValues; //!< stores the speed values
	std::vector<sf::Vector2i> m_Positions; //!< stores the positions 
	std::vector<float> m_health; //!< stores health 
	std::vector<float> m_attack; //!< stores attack
	std::vector<std::string> m_texture;	//!< stores texture id
	int m_startOfVampires; //!< stores an int used for to determine when the vampires start in a vector

};