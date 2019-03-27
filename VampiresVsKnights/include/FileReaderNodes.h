#pragma once
#include <fstream>
#include <sstream>
#include <string>
#include <vector>

#include <SFML/Graphics.hpp>

/*! Another file that stores what nodes are going to be put into the game*/

class FileReaderNodes
{
public:
	 
	FileReaderNodes(std::string p_Nodes); //!< Constructs the file loader for the nodes
										  /*!
										  \param p_Nodes gets passed in a string with information on the nodes
										  */
	std::vector<sf::Vector2i> getNodeID(); //!< Gets the positions of the node
	std::vector<std::string> getNodeTypes(); //!< Gets a string each with a node type
	std::vector<float> getCost(); //!< Gets the cost of moving over the node


private:

	std::vector<sf::Vector2i> m_nodeID; //!< Stores the nodes position
	std::vector<std::string> m_nodeTypes; //!< Stores the nodes types
	std::vector<float> m_cost; //!< stores the cost for moving over the node

};